# About

An executable that integrates your desired repo content to text form that can be used to provide context to an LLM.

## License

This project uses the MIT license.

# Who/What does this project exist to serve?

This project is for:
<ul>
  <li>Back and forth code reports between the coder and an LLM</li>
</ul>

# What problem does this project exist to solve?

Sometimes, a developer dislikes ‘vibe-coding’ but wants to continue coding in the traditional sense. Well this project helps you find out how reliant you can be on AI while still following the traditional pursuit.

# What solution does this project hope to achieve?

Providing readable, simple, and comprehensive text to the user’s clipboard so they can paste it all into ChatGPT.

# What solution is required to alleviate this project and competing subscriptions if necessary?

Copying and pasting code snippets of a given solution and a snippet for each of its dependencies.

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
<li>**In Solution Explorer**, right-click HelloWorld.</li>
<li>Click "Set as Startup Project".</li>
<li>Press **Run** or **Local Windows Debugger**.</li>
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

