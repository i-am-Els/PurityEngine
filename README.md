# Build Setup Process _(for contributors)_
1. Ensure `vcpkg` is installed. Get the package manager on your machine.
- clone `vcpkg` into any location of your choice,

> ```shell
> git clone https://github.com/microsoft/vcpkg.git
> ```

- cd into the install path and run the bootstrap bat file.

> ```shell
> cd vcpkg; .\bootstrap-vcpkg.bat
> ```

2. Create a new `CMakeUserPresets.json` in the root of the project to accompany the `CMakePresets.json`. Your CMakeUserPresets.json should look something like this...
```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "debug",
      "inherits": "base",
      "environment": {
        "VCPKG_ROOT": "path-to-vcpkg"
      }
    },
    {
      "name": "release",
      "inherits": "debug",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release",
        "CMAKE_CXX_FLAGS": "/DWIN32 /D_WINDOWS /O2 /GR /EHsc"
      }
    }
  ],
  "buildPresets": [
    {
      "name": "default-build-windows",
      "displayName": "Default",
      "configurePreset": "debug",
      "description": "Vanilla build"
    },
    {
      "name": "release_build_windows",
      "configurePreset": "release",
      "displayName": "Release",
      "description": "Vanilla Build"
    }
  ]
}
```
You can directly copy this and change the `VCPKG_ROOT` path value to the instance location of `vcpkg` on your machine.
> Note:
> Do not commit the `CMakeUserPresets.json` file, **Ever!!!**
## Optionally

>3. To download the dependencies listed in the project's vcpkg.json, run this:
> > ```shell
> > vcpkg install --triplet <triplet>
> > ```  
> > for example, in my Visual Studio project, I use this:
> > ```shell
> > vcpkg install --triplet x64-windows
> > ```

## Cont'd
4. Then in your IDE(in my case Visual Studio 2022), reset Cache and Configure the project.
5. Build all projects.
6. Run the `install` Executables. 

> There are executables such as `Game.exe` and `PurityEditor.exe` in the install directories `${projectDir}/out/install/${presetName}/bin`, accompanied by the required runtime artefacts. Running these executables instead of the ones in the target binary directories will resolve the `DLL not found errors`. 

> No more manually copying dlls to executable location. You get the latest build in the install directory.

For more help, check the vcpkg documentation _[here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?pivots=shell-powershell)_

To resolve relative path issues, use the json snippet below to setup your `launch.vs.json`
```json
{
  "version": "0.2.1",
  "defaults": {},
  "configurations": [
    {
      "type": "default",
      "project": "CMakeLists.txt",
      "projectTarget": "PurityEditor.exe (Install)",
      "name": "PurityEditor.exe (Install)",
      "currentDir": "${workspaceRoot}"
    },
    {
      "type": "default",
      "project": "CMakeLists.txt",
      "projectTarget": "PurityGem.exe (Install)",
      "name": "PurityGem.exe (Install)",
      "currentDir": "${workspaceRoot}"
    }
  ]
}
```

## VS Code Setup
Everything above also applies when using VS Code. Install the following extensions:

- `CMake Tools` (`ms-vscode.cmake-tools`)
- `C/C++` (`ms-vscode.cpptools`)
- `Child Process Debugging` [Find it here](https://marketplace.visualstudio.com/items?itemName=albertziegenhagel.childdebugger)

1. Open the repository root in VS Code.
2. Make sure `VCPKG_ROOT` is available in the VS Code environment, or set it in `CMakeUserPresets.json` as described above.
3. Open the Command Palette and run `CMake: Select Configure Preset`, then select `debug`.
4. Run `CMake: Configure` and then `CMake: Build` from the Command Palette. The build preset produces the binaries under `out/build/debug`.
5. Run `CMake: Install` before launching the editor or game. The runnable executables are installed under `out/install/debug/bin` so their runtime DLLs are available.
6. Open the Run and Debug view and create a C++ launch configuration for the installed executable. Use the repository root as the working directory and select `PurityEditor.exe` or `PurityGem.exe` from `out/install/debug/bin`.
7. Use the `Child Process Debugging` extension when the process being debugged starts additional executables. Start the parent process through the Run and Debug view so child-process attachment can be enabled by the extension.

For a repeatable launch configuration, create `.vscode/launch.json` with the following and adjust the executable name when needed:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "PurityEditor (Install)",
      "type": "cppvsdbg",
      "request": "launch",
      "program": "${workspaceFolder}/out/install/debug/bin/PurityEditor.exe",
      "cwd": "${workspaceFolder}/out/install/debug/bin",
      "stopAtEntry": false,
      "console": "externalTerminal",
      "autoAttachChildProcess": true
    },
    {
      "name": "PurityGem (Install)",
      "type": "cppvsdbg",
      "request": "launch",
      "program": "${workspaceFolder}/out/install/debug/bin/PurityGem.exe",
      "cwd": "${workspaceFolder}/out/install/debug/bin",
      "stopAtEntry": false,
      "console": "externalTerminal",
      "autoAttachChildProcess": true
    }
  ]
}
```

## CLion Setup
Everything above is to configure `Visual Studio Community`. Do the following in addition if you wish to build the projects and contribute using either `CLion` or `VS Code`...
### CLion
1. Open CLion configurations.
2. If no targets are set, create new targets for the following(Select `CMake Application` as Target type).
    - PurityEditor `exe`
    - Purity `dll`
    - PurityGem `exe`
    - Commons `dll`
    - IsleMath `dll`
    - ImGuiFileDialog `lib`
3. For all Targets of type `exe`, Set the `Executable` field to the target found in the `install` folder.
   - > e.g C:\Path-to-PurityEngine\out\install\debug\bin\PurityGem.exe

   - Make sure the executables selected are the one located in the install folder at `out/install/debug/bin` for example
4. Set the working directory of all the targets to the `$ProjectFileDir$` macro.
5. Optionally, make the toolchain the Visual Studio Toolchain. Not tested with MinGW.