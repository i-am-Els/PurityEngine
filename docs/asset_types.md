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
  "start_up_scene" : "assets/scenes/default_scene.pscene",

  "projectDB" : "assets/Game.peDB"
}

```
- `"project_name"` is the name of the project, also what goes into the executable name.
- `"start_up_scene"` points to the relative path to the PurityEditor launch start up scene `.puritys` file.
- `"projectDB"`points to the asset database file in the project. 

### Purity Asset DB file `*.peDB`
This DB file represents assets that need to be present in the assetDatabase at runtime and they are loaded on launch.
```json
{
  "id": "1234567890123456",
  "assets" : [
    {
      "id": "3456789012345612",
      "path": "<file-with-uuid-0-rel-path-to-project-root>.puritya"
    },
    {
      "id": "8901234561234567",
      "path": "<file-with-uuid-1-rel-path-to-project-root>.pmeta"
    }
  ]
}
```
- `"assets"`is a list of pairs of asset `id` (_key_) and their relative `path`s(_value_). These assets are the `.puritya` files in the project directory.

Note: In memory, assetDB is resolved to a map of `id` (_key_) to asset relative `path`s(_value_).

### Purity scene description files `*.pscene`
The structure of the scene file describes the hierarchical tree of entity transforms.

> Note: A pscene is a `PAsset file` with its `source` set to `LevelAsset` and its `parentID` set to `0`. This is **mandatory**

```json
{
  "id": "6543210987654321",
  "source" : "scene",
  "type_" : "LevelAsset",
  "data_" : {
     "children": [
        {
           "id": "4321210965438765",
           "name": "box",
           "components": {
              "transformComponent": {},
              "tagComp" : {
                 "tag" : 0
              },
              "idComp" : "4321210965438765",
              "meshComponent": 1
           },
           "children": []
        }
     ]
  },
  "ref_assets": []
}
```

It is treated as a `LevelAsset` just like a `prefab` with the source being the only difference and the `data_` contained in them. The `source` attribute is the most essential in differentiating a scene from a prefab.

### Purity asset files `*.passet`
The structure of asset files vary, and can be determined by the asset source i.e. whether it was imported as an asset or created in the editor as a prefab.

#### The Asset source enum 
- Asset
- Prefab

##### 'ASSET' asset
An 'Asset' asset is one that was imported through the fileIO system. It has an external source. 

```json
{
  "id": "6543210987654321",
  "source" : "asset",
  "type_" : "StaticMeshAsset",
  "data_" : {
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
- `"source"` describes the source enum of an asset, `"prefab"` or `"asset"`. Asset sources are usually just `"asset"`.
- `"type_"` specifies the asset type.
- An `parentID` of `0` means it is a root prefab.
- `"data_"` holds the asset data in engine-compatible processed format. 
- `"ref_assets"` is an array of other possible assets in the project that this asset makes reference to.

##### PREFAB asset
```json
{
  "id" : "4321210965438765",
  "source" : "prefab",
  "type_" : "LevelAsset",
  "data_" : {
    "components" : [
      {
        "transformComponent": {
          "position" : [0, 0, 0],
          "scale" : [1, 1, 1],
          "rotation" : [0, 90, 0],
          "children": ["3876543212109654", "1096543876543212"]
        },
        "tagComp" : {
          "tag" : 0
        },
        "idComp" : "8765432165432109",
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
    "4321654387652109",
    "6543210987654321",
    "9028432490545838"
  ]
}
```
In the example above we have a `PREFAB` asset. This is what an asset created in the editor as a prefab looks like.
- `"source"` describes the source enum and is the first item in the source array.
- The second element of the `"source"` value array is the prefab `parentID`. The prefab parent is the asset/entity which this prefab is made/cloned from. 
- An `parentID` of `0` means it is a root prefab.
- `"data_"` contains entity/prefab information.
- `"ref_asset_index"` is the index of the referenced asset in `ref_assets` array.
<hr>

## REFERENCE ASSET
A `Ref<T>` asset such as `Ref<Texture>` is typically a smart pointer or reference-counted wrapper around an object of type T, in this case `Texture`. It is commonly used in game engines or graphics libraries to manage the lifetime of resources (like textures) efficiently. The purpose of `Ref` is to handle reference counting, ensuring that resources are properly released when no longer needed, while avoiding memory leaks or dangling pointers.

Here’s an overview of how you can implement something like `Ref<T>` in C++:

---

### Implementation of `Ref<T>`
Below is a simplified implementation of a `Ref` class for reference counting:

```cpp
#include <iostream>
#include <atomic>

// Forward declaration
template<typename T>
class Ref;

// Base class for reference-counted objects
class RefCounted {
protected:
    mutable std::atomic<int> refCount{0};

    virtual ~RefCounted() = default; // Ensure proper polymorphic destruction

    template<typename T>
    friend class Ref;

public:
    void addRef() const {
        refCount.fetch_add(1, std::memory_order_relaxed);
    }

    void release() const {
        if (refCount.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            delete this;
        }
    }

    int getRefCount() const {
        return refCount.load(std::memory_order_relaxed);
    }
};

// Example texture class
class Texture : public RefCounted {
public:
    Texture() {
        std::cout << "Texture created\n";
    }

    ~Texture() {
        std::cout << "Texture destroyed\n";
    }
};

// Reference-counting wrapper
template<typename T>
class Ref {
private:
    T* ptr{nullptr};

public:
    Ref() = default;

    explicit Ref(T* object) : ptr(object) {
        if (ptr) {
            ptr->addRef();
        }
    }

    Ref(const Ref& other) : ptr(other.ptr) {
        if (ptr) {
            ptr->addRef();
        }
    }

    Ref(Ref&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    ~Ref() {
        if (ptr) {
            ptr->release();
        }
    }

    Ref& operator=(const Ref& other) {
        if (this != &other) {
            if (ptr) {
                ptr->release();
            }
            ptr = other.ptr;
            if (ptr) {
                ptr->addRef();
            }
        }
        return *this;
    }

    Ref& operator=(Ref&& other) noexcept {
        if (this != &other) {
            if (ptr) {
                ptr->release();
            }
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* get() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

int main() {
    Ref<Texture> tex1(new Texture()); // Texture created
    Ref<Texture> tex2 = tex1;         // Shared ownership
    Ref<Texture> tex3;                // Empty ref
    tex3 = tex2;                      // Shared ownership
    // All references go out of scope; Texture destroyed

    return 0;
}
```

---

### Key Features of the Implementation:

1. **Reference Counting:**
   - The `RefCounted` base class tracks the reference count using an `std::atomic<int>` to allow thread-safe usage.

2. **Automatic Lifetime Management:**
   - The `Ref` class ensures that the underlying object is deleted when the last reference is released.

3. **Copy and Move Semantics:**
   - Copying a `Ref` increments the reference count.
   - Moving transfers ownership without incrementing the reference count.

4. **Polymorphic Destruction:**
   - The destructor of `RefCounted` is declared `virtual` to ensure proper destruction of derived classes.

5. **Safety:**
   - The `Ref` class handles null pointers gracefully and provides convenient syntax for accessing the underlying object.

---

### Usage in a Game Engine
In a game engine, `Ref<T>` might be used for resources like textures, meshes, or shaders. These resources are often expensive to create and destroy, so reference counting ensures they are shared and reused efficiently.

For example:
- A `Texture` might be loaded once, stored in a cache, and shared across multiple objects.
- When all references to the `Texture` are gone, it is automatically released from memory.

Let me know if you'd like further enhancements to this implementation or its integration with a real-world game engine!

<hr>
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

