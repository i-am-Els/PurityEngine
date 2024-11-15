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
        "VCPKG_ROOT": "C:/path/to/vcpkg"
      }
    },
    {
      "name": "release",
      "inherits": "debug",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
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

> There are executables such as `Game.exe` and `PnTEditor.exe` in the install directories `${projectDir}/out/install/${presetName}/bin`, accompanied by the required runtime artefacts. Running these executables instead of the ones in the target binary directories will resolve the `DLL not found errors`. 

> No more manually copying dlls to executable location. You get the latest build in the install directory.

For more help, check the vcpkg documentation _[here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?pivots=shell-powershell)_