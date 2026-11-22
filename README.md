# Engineering2D

A 2D game engine written in C++ with SDL3.

<!-- TODO: add one or two lines about what the engine does today (e.g. window, input, textures, actors) -->

## Installing Prerequisites (Once per Computer)

### Windows

- **Visual Studio Community**: install the "Desktop Development with C++" workload.
  (If CMake doesn't appear as installed, install it from [cmake.org/download](https://cmake.org/download), choosing "Add CMake to the system PATH" during installation.)
- **Git**: [git-scm.com](https://git-scm.com)

### macOS

```bash
xcode-select --install
brew install cmake pkg-config
```

### Check that Git and CMake are installed

```bash
git --version
cmake --version
```

## Install vcpkg (Once per Computer)

### Windows (PowerShell)

```powershell
cd C:\
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
setx VCPKG_ROOT "C:\vcpkg"
```

Close and reopen PowerShell, then check the variable:

```powershell
echo $env:VCPKG_ROOT
```

Expected result: `C:\vcpkg`

### macOS (Terminal)

```bash
cd ~
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
echo 'export VCPKG_ROOT="$HOME/vcpkg"' >> ~/.zshrc
```

Close and reopen Terminal, then check the variable:

```bash
echo $VCPKG_ROOT
```

Expected result: `/Users/<you>/vcpkg`

## Generate the Project and Build

### Windows

Open a terminal in the project's root directory and run:

```bash
cmake --preset default
cmake --build build
```

### macOS

```bash
cmake --preset xcode
cmake --build build-xcode
```

**Commands information**

- `cmake --preset default` generates the project.
- `cmake --build build` builds the executable.

> **Note:** the first time you generate the project, vcpkg downloads and compiles SDL3. This can take several minutes.

## Run

The build copies the `graphics/` folder next to the executable, and the game loads its images with relative paths such as `graphics/LonerA.bmp`. Run the executable from its own folder so those paths are found.

### Windows (PowerShell)

```powershell
cd build\Debug
.\2DGameEngine.exe
```

### macOS (Terminal)

```bash
cd build-xcode/Debug/
./2DGameEngine
```

You should see a window with a magenta background.