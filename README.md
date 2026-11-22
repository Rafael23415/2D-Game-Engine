## Installing Prerequisites (Once per Computer)

### Windows

Visual Studio Community - Install "Desktop Development with C++" workload
(If CMake doesn't appear as installed, install through cmake.org/download, choosing “Add CMake to the system PATH” during installation)

Git - git-scm.com

### macOS

XCode - xcode-select --install
Homebrew - brew install cmake pkg-config

## Check both are installed

```git --version```

```cmake --version```



## Install vcpkg (Once per Computer)

### Windows (PowerShell)

```cd C:\```
```git clone https://github.com/microsoft/vcpkg.git```
```cd vcpkg```
```.\bootstrap-vcpkg.bat```

### macOS (Terminal)

```cd ~```
```git clone https://github.com/microsoft/vcpkg.git```
```cd vcpkg```
```./bootstrap-vcpkg.sh```



## Generate Project and Create Build

```cmake --preset default => Generates the project```

```cmake --build build => Creates an executable```