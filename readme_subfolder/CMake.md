# CMake integration
This project integrates with [https://cmake.org](CMake) with the goal to:
<ul>
<li>Enable cross-platform builds</li>
<li>Eliminate reliance on manually creating Visual Studio projects</li>
<li>Support clean out-of-source builds</li>
</ul>

## Why use CMake?
This project uses CMake as its build system.

CMake allows us to:
<ul>
<li>Generate a Visual Studio .sln automatically</li>
<li>Keep the project IDE-independent</li>
<li>Easily expand the project later (libraries, multiple executables, testing, etc.)</li>
<li>Avoid committing Visual Studio-specific files</li>
</ul>

Instead of manually managing .sln and .vcxproj files, CMake can generate them consistently in a /build folder.

## CMake configuration
`CMakeLists.txt`
```
cmake_minimum_required(VERSION 3.20)

project(RepoContextClipboardForAi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(RepoContextClipboardForAi main.cpp)
```

What this does:
<ul>
<li>`cmake_minimum_required(VERSION 3.20)` ensures a compatible CMake version</li>
<li>`project(HelloWorld ...)` defines the solution name and language</li>
<li>`set(CMAKE_CXX_STANDARD 17)` enforces C++17</li>
<li>`add_executable(HelloWorld main.cpp)` creates an executable target named HelloWorld from main.cpp</li>
</ul>

When CMake runs, it generates:
<ul>
<li>`RepoContextClipboardForAi.sln`</li>
<li>Associated `.vcxproj` files</li>
</ul>

## CMake build procedure
## 1: Building a Visual Studio Project (2022)
From the project root:
```
cmake -S . -B build -G "Visual Studio 17 2022"
```

## 2: Building the compiled .exe
To build the program .exe, you can do either of the following:
### Building the solution through Visual Studio
<ol>
<li>Navigate to the build/ directory.</li>
<li>Open HelloWorld.sln.</li>
<li><b>In Solution Explorer</b>, right-click HelloWorld.</li>
<li>Click "Set as Startup Project".</li>
<li>Press <b>Run</b> or <b>Local Windows Debugger</b>.</li>
</ol>

### Through the command line
After running the following command:
```
cmake --build build --config Debug
```
The executable will be output to:
```
build/Debug/RepoContextClipboardForAi.exe
```