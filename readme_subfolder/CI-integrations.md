## This project now works with GitHub Actions to ensure the CMake build commands work on a given local Windows machine.
You can check the CI script in `.github/workflows/windows-build.yml`.

### github/workflows/windows-build.yml
```
name: Windows CMake Build

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: windows-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Configure CMake
        run: cmake -S . -B build -G "Visual Studio 17 2022"

      - name: Build
        run: cmake --build build --config Release
```
