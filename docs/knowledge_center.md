
# Knowledge Center
## STUDY 1 - Specs and Handles

What is the deal with the `spec` and `handle` keywords? what are they and how they different from plain `structs`?

### Handles

**Definition**: A "handle" is an abstract reference or identifier to a resource (like a file, object, or system resource). Rather than working directly with the resource, programs work with the handle, which the system uses to manage access to the actual resource.

**Usage**: Handles are often used in systems programming to manage resources like files, windows, or database connections. For instance, instead of working with a file directly, the program opens the file and gets a file handle (an identifier), which it then uses to read, write, or close the file.

Handles are typically used to reference external or system-level resources, like:
- Files (opened files in an operating system),
- 3D meshes or textures loaded into a renderer,
- Network sockets, database connections, or system objects.

The key point here is that these resources are often managed by external systems (like the OS or a rendering engine) and require controlled access. A handle allows you to refer to these resources without exposing their internal workings.

#### When Handles Are Suitable:
- The resource is large or requires special access, like a file or a GPU buffer (3D mesh, texture).
- The resource is managed externally, like when the OS or a rendering engine allocates and frees memory (e.g., OpenGL textures or file descriptors).
- The resource needs to be safely shared among different systems or processes.

#### When Handles Are Not Necessary:
- The resource is small, like a simple struct (e.g., a transform).
- You have full ownership and control over the resource in your code, meaning there's no need to abstract or manage it externally.

### Specs

A spec (short for specification) is essentially a document or description that outlines the expected behavior, structure, or requirements of a system, component, or API. Specs serve as a blueprint for how something is supposed to work. Think of them as guidelines that describe what a program, module, or system should do—without necessarily diving into how it's done.A spec (short for specification) is essentially a document or description that outlines the expected behavior, structure, or requirements of a system, component, or API. Specs serve as a blueprint for how something is supposed to work. Think of them as guidelines that describe what a program, module, or system should do—without necessarily diving into how it's done.

A Status Effect is something that applies some change to an attribute or property of an entity, like:

- Increasing health by 50.
- Reducing movement speed by 20% for 5 seconds.
- Granting invincibility for 10 seconds.

To implement these status effects, both a spec and a handle are involved.

A spec for a Status Effect represents a detailed configuration or blueprint for that effect. This spec defines the specific rules, attributes, and conditions of the effect but doesn't represent the effect as it’s applied in the game world.
