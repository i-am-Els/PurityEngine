###### This Documentation is a property of Eniola Olawale
##### Copyright &copy; Eniola Olawale 2024. All rights reserved.

<hr>

# Purity - 3D Game Engine.
<hr>

## Asset Database - Asset Types
This document lists out the external asset types that will be supported by this engine.
The `FILE I/O` System handles importation of asset file and converts them into the _internal data representation_.  
This internal representation is of a `BaseAsset` type that holds a `type` attribute. specifying which system makes use of it.

<hr>

## Asset Types
### Import Types
Textures & Images
- `*.png`, `*.bmp`
- `*.tif`,  `*.tga`
- `*.jpeg`, `*.jpg`

Sound
- `*.wav`
- `*.aac`
- `*.ogg`
- `*.mp3`

Models
- `*.fbx` 
- `*.obj`

Animation files
- `*.fbx`

### Internal Types
Assets
- `*.passet`

Scripting
- `*.pmeta`

Script3D
- `*.script3D`

### Export Types
Animation
- `*.fbx`

Scene Description
- `*.pscene`

AssetDB Repository file
- `*.peDB`

Project File
- `*.pproject`

Note: First line in any section takes priority in MVP phase.

### Assets Sub-types
- TextureAsset.
- SpriteAsset (For UI).
- ShaderAsset (Shader Struct Handle).
- MeshAsset (Animatable Mesh).
- SkeletonAsset (Object Rig, can be extracted from a Mesh Asset, and applied to another).
- StaticMeshAsset.
- MaterialAsset.
- SplineAsset.
- PolygonMeshAsset.
- SoundSourceAsset.
- 3DSoundSourceAsset.
- LevelAsset (Scene description nodes or contents and prefab such as an `Entity` Prefab or `Behaviour` scripts).
- ParticleAssets.
- RenderMapAssets (CubeMap, Environment Max etc).

<hr>

## Internal Structure of Files
This documents the internal layout of this json files.

### Purity project file `*.pproject`
The layout and key-value pair looks like so: 
```json
{
  "project_name": "Game",
  "start_up_scene" : "./assets/scenes/default_scene.pscene",

  "projectDB" : "./assets/Game.peDB"
}

```
- `"project_name"` is the name of the project, also what goes into the executable name.
- `"start_up_scene"` points to the relative path to the PurityEditor launch start up scene `.puritys` file.
- `"projectDB"`points to the asset database file in the project. 

### Purity Asset DB file `*.peDB`
This DB file represents assets that need to be present in the assetDatabase at runtime and they are loaded on launch.
```json
{
  "id": 1234567890123456,
  "assets" : [
    {
      "id": 3456789012345612,
      "path": "<file-with-uuid-0-rel-path-to-project-root>.puritya"
    },
    {
      "id": 8901234561234567,
      "path": "<file-with-uuid-1-rel-path-to-project-root>.pmeta"
    }
  ]
}
```
- `"assets"`is a list of pairs of asset `id` (_key_) and their relative `path`s(_value_). These assets are the `.puritya` files in the project directory.

Note: In memory, assetDB is resolved to a map of `id` (_key_) to asset relative `path`s(_value_).

### Purity scene description files `*.pscene`
The structure of the scene file describes the hierarchical tree of entity transforms.

### Purity scene description files `*.passet`
The structure of asset files vary, and can be determined by the asset source i.e. whether it was imported as an asset or created in the editor as a prefab.

#### The Asset source enum 
- Asset
- Prefab

##### 'ASSET' asset
An 'Asset' asset is one that was imported through the fileIO system. It has an external source. 

```json
{
  "id": 6543210987654321,
  "source" : ["asset"],
  "parentID": 0,
  "type" : "StaticMeshAsset",
  "data" : {
    "vertices" : {
      "position": [],
      "textureCoord" : [],
      "normal": []
    },
    "indices" : []
  },
  "ref_assets": []
}
```
The Keys:
- `"id"` is a uuid assigned to the asset file. it is also reference in the `"assets"` map in assetDB file.
- `"source"` describes the source enum of an asset, `"prefab"` or `"asset"`. Asset sources are usually just `["asset"]`.
- `"type"` specifies the asset type.
- An `parentID` of `0` means it is a root prefab.
- `"data"` holds the asset data in engine-compatible processed format. 
- `"ref_assets"` is an array of other possible assets in the project that this asset makes reference to.

##### PREFAB asset
```json
{
  "id" : 4321210965438765,
  "source" : "prefab"
  "parentID": 0,
  "type" : "LevelAsset",
  "data" : {
    "components" : [
      {
        "transformComponent": {
          "position" : [0, 0, 0],
          "scale" : [1, 1, 1],
          "rotation" : [0, 90, 0],
          "children": []
        },
        "tagComp" : {
          "tag" : 0
        },
        "idComp" : 8765432165432109,
        "meshComponent" : {
          "ref_asset_index" : 1
        },
        "renderComponent": {
          "isVisible": true
        },
        "behaviourComponents": [
          "<scriptA-path-relative-to-project-root>",
          "<scriptB-path-relative-to-project-root>",
          "<scriptC-path-relative-to-project-root>"
        ]
      }
    ]
  },
  "ref_assets": [
    4321654387652109,
    6543210987654321,
    9028432490545838
  ]
}
```
In the example above we have a `PREFAB` asset. This is what an asset created in the editor as a prefab looks like.
- `"source"` describes the source enum and is the first item in the source array.
- The second element of the `"source"` value array is the prefab `parentID`. The prefab parent is the asset/entity which this prefab is made/cloned from. 
- An `parentID` of `0` means it is a root prefab.
- `"data"` contains entity/prefab information.
- `"ref_asset_index"` is the index of the referenced asset in `ref_assets` array.

<hr>

## Scripts - Behaviour Component

The scripts are C++ files for now, until a scripting system is introduced. To serialize scripts, we need to create a meta file for the script.
The meta file holds the json structure of the serializable contents(mostly primitive types) in the script class.

It is important that these scripts implement the BehaviourComponent class if they will be added to entities and serialized with the scene description.  

##### SCRIPT `.pmeta`
```json
{
  "id" : 2109654432138765,
  "path": "<ref-script-path-relative-to-project-root>",
  "serializable_fields" : {
    "color": [0, 0, 1, 1],
    "camera_offset" : [0.0, 10.0, -35.0]
  }
}
```

Every script should have an accompanying `.pmeta` file of the same name. and in the same directory that contains its serialization details. 
In this case:

```c++
#include "purity.h"
using namespace isle_engine::math;
using namespace purity::graphics; 

class CameraOffset : public PBehaviourScriptComponent{
public:
    Color color {0, 0, 1, 1};
    Vector3f camera_offset { 0.0f, 10.0f, -35.0f};
    
    void start() override{
        // ...
    }
    
    void update(float deltaTime) override{
        // ...
    }
};
```

