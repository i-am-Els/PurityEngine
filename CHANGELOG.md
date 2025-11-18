# Changelog

All notable changes to the PurityEngine project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- **Asset Management System**: Complete implementation of asset database with type strategies and query specifications
  - `AssetDB` service with concrete implementation for asset loading, querying, and management
  - Type-specific asset handling strategies (Scene, Prefab, Project assets)
  - Asset query specifications for filtering and searching assets
  - Reference-counted asset handles for memory management
  - Asset utility functions for common operations
  - Support for `.passet`, `.pscene`, `.peDB`, and `.pproject` file formats
  - JSON schema validation for asset files

- **Core Engine Systems**:
  - Entity Component System (ECS) with full entity registry and handle-based architecture
  - Component system with ID, Tag, Transform, Mesh, Camera, and Script components
  - Service locator pattern for decoupled system management
  - Layer system with mask-based filtering for rendering and physics
  - Event system with keyboard, mouse, and window events
  - Input system for centralized input handling
  - Logging system with multiple severity levels

- **Rendering System**:
  - OpenGL-based renderer with shader management
  - Vertex Array Objects (VAO) and Buffer Objects (VBO/EBO) abstraction
  - Basic shader support with vertex and fragment shaders
  - Mesh rendering system with component-based architecture
  - Camera system with projection matrices
  - Color utilities for RGBA manipulation

- **Transform System**:
  - Hierarchical transform components with parent-child relationships
  - Transform system for managing entity positions, rotations, and scales
  - 3D transform calculations using IsleMath library

- **Scene Management**:
  - Scene serialization and deserialization
  - Entity prefab system for reusable game objects
  - Scene asset loading and saving

- **File I/O**:
  - Mesh importer with Assimp integration for loading 3D models
  - File I/O utilities for reading and writing project files
  - Handle-based resource management

- **Project Structure**:
  - `Commons` library for shared utilities (UUID generation, serialization)
  - `Purity` core engine library with modular architecture
  - `PurityEditor` GUI application for scene editing
  - `PurityGem` project management tool
  - `Game` sample application demonstrating engine usage
  - Vendor libraries: `isle_math` (math library) and `ImGuiFileDialog` (file dialogs)

- **Build System**:
  - CMake-based build configuration with presets
  - vcpkg integration for dependency management
  - Support for Visual Studio, CLion, and VS Code
  - Install targets for easy deployment

- **Dependencies**:
  - GLFW3 for windowing and input
  - GLAD for OpenGL loading
  - ImGui with docking support for editor UI
  - Assimp for 3D model importing
  - Cereal for serialization
  - nlohmann-json for JSON parsing
  - json-schema-validator for schema validation
  - Google Test for unit testing

- **Sample Assets**:
  - Default scene setup with quad prefab
  - Example game project structure
  - Test models (bunny, suzanne, teapot, Stanford bunny, Newell teaset)
  - Basic shader examples (vertex and fragment shaders)

### Documentation
- Added comprehensive build setup guide for contributors
- Added knowledge center documentation covering specs and handles
- Added asset types documentation
- Added mesh system documentation
- Added application flow documentation
- JSON schema examples for project file formats

## Project Information

**Current Version**: 1.0.0  
**Engine**: PurityEngine - A modern C++ game engine with ECS architecture  
**License**: Not specified  
**Contributors**: Eniola Emmanuel Olawale (@i-am-Els)

---

*This CHANGELOG was generated based on the initial project setup and asset management system merge (PR #31).*
