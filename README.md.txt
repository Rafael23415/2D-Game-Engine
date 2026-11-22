Check git and CMake

git --version
cmake --version

Install vcpkg

cd C:\
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

Go to the project directory and add vcpkg baseline

setx VCPKG_ROOT "C:\vcpkg"
(reopen powershell)
& "$env:VCPKG_ROOT\vcpkg.exe" x-update-baseline --add-initial-baseline

Run vcpkg and generate project

cmake --preset default

Compile project

cmake --build build