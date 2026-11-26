# 2D Game Engine

A 2D game engine written in C++ with SDL3.

<!-- TODO: add one or two lines about what the engine does today (e.g. window, input, textures, actors) -->

## 1. Installing Prerequisites (Once per Computer)


> **Important:** If you already installed vcpkg and created the VCPKG_ROOT environment variable, you can jump to topic 3.


### Windows

- **Visual Studio Community**: install the "Desktop Development with C++" workload.
  (If CMake doesn't appear as installed, install it from [cmake.org/download](https://cmake.org/download), choosing "Add CMake to the system PATH" during installation.)
- **Git**: [git-scm.com](https://git-scm.com)

### macOS

```bash
xcode-select --install
brew install cmake pkg-config
```

### 1.1. Check that Git and CMake are installed

```bash
git --version
cmake --version
```

## 2. Install vcpkg (Once per Computer)

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

## 3. Generate the Project and Build

### Windows

Open a terminal in the project's root directory and run:

```bash
cmake --preset default
```

### macOS

```bash
cmake --preset xcode
```

**Commands information**

- `cmake --preset default` generates the project, being located inside the created 'build' folder.

> **Note:** the first time you generate the project, vcpkg downloads and compiles SDL3. This can take several minutes.

## 4. Run

The build copies the `graphics/` folder next to the executable, and the game loads its images with relative paths such as `graphics/LonerA.bmp`. Run the executable from its own folder so those paths are found.

### Windows (PowerShell)

```powershell
cmake --build build

cd build\Debug
.\2d-game-engine.exe
```

### macOS (Terminal)

```bash
cmake --build build-xcode

cd build-xcode/Debug/
./2d-game-engine
```
**Commands information**

- `cmake --build build` builds the executable.

You should see a window with a dark green background.
