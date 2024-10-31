###### This Documentation is a property of Eniola Olawale
##### Copyright &copy; Eniola Olawale 2024. All rights reserved.

<hr>

# PnT - 3D Game Engine.
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
- `*.pnta`

Script3D
- `*.script3D`

### Export Types
Animation
- `*.fbx`

Scene Description
- `*.pnts`

AssetDB Repository file
- `*.pntDB`

Project File
- `*.pnt`

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
- LevelAsset (Scene description nodes or contents and prefab such as an `Entity` Prefab).
- ParticleAssets.
- RenderMapAssets (CubeMap, Environment Max etc).

<hr>

## Internal Structure of Files
This documents the internal layout of this json files.

### PnT project file `*.pnt`
The layout and key-value pair looks like so: 
```json
{
  "project_name": "Game",
  "start_up_scene" : "./assets/scenes/default_scene.pnts",

  "projectDB" : "./assets/Game.pntDB"
}

```
- `"project_name"` is the name of the project, also what goes into the executable name.
- `"start_up_scene"` points to the relative path to the PnTEditor launch start up scene `.pnts` file.
- `"projectDB"`points to the asset database file in the project. 

### PnT Asset DB file `*.pntDB`
This DB file represents assets that need to be present in the assetDatabase at runtime and they are loaded on launch.
```json
{
  "id": 1234567890123456,
  "assets" : [
    {
      "id": 0,
      "path": "<file-with-uuid-0-rel-path-to-project-root>"
    },
    {
      "id": 1,
      "path": "<file-with-uuid-1-rel-path-to-project-root>"
    }
  ]
}
```
- `"assets"`is a list of pairs of asset `id` (_key_) and their relative `path`s(_value_). These assets are the `.pnta` files in the project directory.

Note: In memory, assetDB is resolved to a map of `id` (_key_) to asset relative `path`s(_value_).

### PnT scene description files `*.pnts`
The structure of the scene file describes the hierarchical tree of entity transforms.

### PnT scene description files `*.pnts`
The structure of asset files vary, and can be determined by the asset source i.e whether it was imported as an asset or created in the editor as a prefab.

#### The Asset source enum 
- Asset
- Prefab

##### 'ASSET' asset
An 'Asset' asset is one that was imported through the fileIO system. It has an external source. 

```json
{
  "id": 6543210987654321,
  "source" : ["asset"],
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
- `"data"` holds the asset data in engine-compatible processed format. 
- `"ref_assets"` is an array of other possible assets in the project that this asset makes reference to.

##### PREFAB asset
```json
{
  "id" : 4321210965438765,
  "source" : [
    "prefab",
    {
      "parentID": 0
    }
  ],
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
        }
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
