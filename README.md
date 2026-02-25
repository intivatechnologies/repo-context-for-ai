# Welcome to a done-for-AI clipboard program
This non-redundant open-ended channel provides AI with context for your project in real-time
so that you don't manually have to perform code snippets and 'codesplaining'.

## Even this README is dedicated to the AI's interpretative abilities
Ever observe a README that seems to have lack of awareness to reason? This README is organized
like a [https://www.inflectra.com/Ideas/Topic/Requirements-Definition.aspx](Software Requirements Specification)
(see **Software Requirements Spec**).

## About

An executable that converts your passed root directory to text and copies it to your clipboard.

## License

This project uses the [./LICENSE](MIT license). Because the solution is not intended to be a standalone product,
I've chosen this license only to validate [https://mikesinclair66.github.io](my work).

## Features (Ctrl/Cmd + Click to open in a new tab)

[./readme_subfolder/CMake.md](CMake integration)

 - [./readme_subfolder/CI-integrations.md](CI integrations - GitHub Actions)[^2]

[!IMPORTANT]
You will have to have [https://cmake.org](CMake) installed to run the [](**installation steps**).

## Software Requirements Spec
### 1. Purpose
1.1 System Overview

<ul>
    <li>
        What the system is
    </li>
    <li>
        The core problem it solves
    </li>
    <li>
        The primary outcome it delivers
    </li>
</ul>

1.2 Success Criteria

Terms for measurable success:
<ul>
    <li>
        Business goal (e.g., acquire 100 users in 3 months)
    </li>
    <li>
        Technical goal (e.g., ~300ms API response time)
    </li>
    <li>
        User goal (e.g., reduce task time by 40%)
    </li>
</ul>

### 2. Users

List user roles and their intent.

2.1 User Roles

Role: Guest
<ul>
<li>
Can browse public content
</li>
<li>
Cannot modify data
</li>
</ul>

Role: Authenticated User
<ul>
<li>
Can create and manage own data
</li>
</ul>

Role: Admin
<ul>
<li>
Can manage users and system settings
</li>
</ul>

(Adjust roles as needed.)

### 3. Functional Requirements

Write as atomic, testable statements.

Format:
```
FR-1: The system shall allow users to register with email and password.
FR-2: The system shall authenticate users via JWT.
FR-3: The system shall allow users to create a project.
FR-4: The system shall allow users to edit or delete their own projects.
FR-5: The system shall allow admins to deactivate users.
```

Guidelines:
<ul>
    <li>
        One behavior per requirement
    </li>
    <li>
        No implementation details
    </li>
    <li>
        Must be testable
    </li>
    <li>
        Use “shall”
    </li>
</ul>

Group by domain if needed:
### Authentication
### Core Feature
### Admin Features

### 4. Non-Functional Requirements
These define system quality.

4.1 Performance
<ul>
<li>
API responses < 300ms under normal load
</li>
<li>
Initial page load < 2 seconds
</li>
</ul>

4.2 Security
<ul>
<li>
Passwords must be hashed
</li>
<li>
HTTPS required
</li>
<li>
Role-based access control
</li>
</ul>

4.3 Scalability
<ul>
<li>
Backend must be stateless
</li>
<li>
Horizontal scaling supported
</li>
</ul>

4.4 Reliability
<ul>
<li>
Daily automated backups
</li>
<li>
System uptime target: 99%
</li>
</ul>

4.5 Maintainability
<ul>
<li>
Modular architecture
</li>
<li>
Minimum 70% unit test coverage
</li>
</ul>

### 5. Data Model
List core entities and key fields.
[!NOTE]
This is kept at high level -- detailed schemas belong elsewhere.

Entity: User
<ul>
<li>
id (UUID)
</li>
<li>
email (string, unique)
</li>
<li>
passwordHash (string)
</li>
<li>
role (enum)
</li>
<li>
createdAt (timestamp)
</li>
</ul>

Entity: Project
<ul>
<li>
id (UUID)
</li>
<li>
ownerId (User reference)
</li>
<li>
title (string)
</li>
<li>
description (text)
</li>
<li>
createdAt (timestamp)
</li>
</ul>

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

## This project now works with GitHub Actions to ensure the CMake build commands work on a given local Windows machine.
You can check the CI script in `.github/workflows/windows-build.yml`.