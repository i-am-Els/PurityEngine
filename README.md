# Setup Process
1. Ensure `vcpkg` is installed. Get the package manager on your machine.
- clone `vcpkg` into any location of your choice,

> ```shell
> git clone https://github.com/microsoft/vcpkg.git
> ```

- cd into the install path and run the bootstrap bat file.

> ```shell
> cd vcpkg; .\bootstrap-vcpkg.bat
> ```

2. Create a new `CMakeUserPresets.json` then make a configure preset that inherits from `base`, set the version config to that of the `CMakePresets.json` found in the project root. Set its environment variables and set `"VCPKG_ROOT"` to something like `C:/path/to/vcpkg` which translates to the location of you `vcpkg` instance.

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

> There are executables such as `Game.exe` and `PnTEditor.exe` in the install directories `${projectDir}/out/install/x64-debug/bin`, accompanied by the required runtime artefacts. Running these executables instead of the ones in the target binary directories will resolve the `DLL not found errors`. 

For more help, check the vcpkg documentation _[here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?pivots=shell-powershell)_