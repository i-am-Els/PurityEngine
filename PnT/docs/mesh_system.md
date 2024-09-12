###### This Documentation is a property of Eniola Olawale
##### Copyright &copy; Eniola Olawale 2024. All rights reseved.

<hr>

# PnT - 3D Game Engine.
<hr>

## ECS - Mesh System
The Entity Component Systems contains a number of systems that relates with their respective components.
 
The Mesh System interacts with the Mesh Component Data Structure in order to get the required information from user side, concerning the mesh needed for the entity.
This system then delivers mesh/geometry data to the Rendering System to work with.
It stores mesh handles.

### Brief - The plan
The Mesh `struct` takes arguments such as `filename`, absolute and/or relative `paths` of mesh in runtime.
- This information is cross-referenced to see if the `mesh handle` already exists in the `asset database`.
- If **false**, a new mesh handle is created for that mesh.
- Otherwise, the mesh struct is mapped to the existing handle as an `instance`.

`READ I/O` operation on a mesh from disk into the project is a one time operation for every _mesh/asset_, however the `UPDATE I/O` operation is performed when the external reference of the mesh is marked `dirty`.

__Note__: A dirty asset is discovered only when its containing folder is loaded in the content browser. A cross-check is performed to re-import assets that have been edited externally.
This check is also done on project launch.
The `HOT RELOAD` flag can be turned off to prevent this behaviour.

### Collaboration with the Rendering System
This system supplies mainly vertex and index data to the renderer. It keeps a `Map` of a pair of `mesh` to `a list of instance transforms`.
In the render loop, the map is queried and using `instanced rendering` all the transform components in the list of instance transforms are rendered in a single draw call. 
