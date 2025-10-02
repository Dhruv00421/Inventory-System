# Inventory

Simple desktop inventory UI built with C++ (C++19), OpenGL (3.3 core), GLFW, GLEW and Dear ImGui.

## Overview
This project provides a minimal graphical inventory manager. The app uses Dear ImGui for the UI and OpenGL for rendering. Inventory items are kept in-memory; there is no persistence (yet). Main UI operations:
- Add Items
- View Inventory
- Update Item
- Delete Item

## Features
- Cross-platform libraries (GLFW / GLEW) with OpenGL 3.3 core profile
- Immediate-mode UI via Dear ImGui
- Small codebase intended for learning or extending into a full app

## Prerequisites
- Visual Studio 2022 (or later) with C++ workload
- Git
- vcpkg (recommended) or prebuilt binaries for GLFW and GLEW
- OpenGL drivers that support at least 3.3

Project expects a C++19 toolset and requests OpenGL 3.3 core in code.

## Recommended dependency installation (vcpkg)
If you use vcpkg, from a Developer Command Prompt:
- bootstrap vcpkg once according to vcpkg docs
- install libraries (example for x64):
  - `vcpkg install glfw3:x64-windows`
  - `vcpkg install glew:x64-windows`
Then integrate vcpkg with Visual Studio:
- `vcpkg integrate install`

## Build with Visual Studio 2022
1. Clone the repo:
   - `git clone https://github.com/Dhruv00421/Inventory-System.git`
2. Open the project/solution:
   - __File > Open > Project/Solution__ and open the `.sln` or the `Inventory.vcxproj`.
3. Set platform:
   - Use __Configuration Manager__ to choose `x64` (or `Win32`) matching your installed library binaries.
4. Configure include/lib directories if not using vcpkg:
   - __Project Properties > Configuration Properties > C/C++ > Additional Include Directories > \$(SolutionDir)Inventory\Dependencies\GLEW\include\GL;$(SolutionDir)Inventory\Dependencies\GLFW\include\GLFW;$(SolutionDir)Inventory\src\Vendors\imgui__
   - Add Preprocessor definitions: `GLEW_STATIC`, `GLEW_STATIC;GLFW_STATIC` (if using static GLEW lib).
   - __Project Properties > Configuration Properties > Linker > Additional Library Directories > \$(SolutionDir)Inventory\Dependencies\GLEW\lib;$(SolutionDir)Inventory\Dependencies\GLFW\lib-vc2022__
   - Add the appropriate `.lib` files to __Project Properties > Linker > Input > `glfw3.lib;glew32s.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib`.
 
5. Build:
   - __Build > Build Solution__

Note: If you use prebuilt GLFW/GLEW DLLs, copy corresponding DLLs (e.g., `glfw3.dll`, `glew32.dll`) to the build output folder next to the `.exe`.

## Run
Start the built executable from Visual Studio or run the .exe from the output folder. The app creates a 960×540 window and shows the ImGui UI. The app initializes ImGui with `#version 330 core` (see `main.cpp`) so make sure drivers support that version.

## Usage
- Launch the app and use the buttons in the main UI:
  - Add Items — opens the add-window to enter name, quantity, price
  - View Inventory — lists items
  - Update Item — select an item and change values
  - Delete Item — remove selected item
- Items are stored only in memory for the current session.

## Project layout (relevant files)
- `src/main.cpp` — program entry, OpenGL/GLFW/ImGui setup and main loop
- `src/Inventory.h` / `src/Inventory.cpp` — inventory model and ImGui windows
- `Vendors/Imgui/` — bundled Dear ImGui sources and bindings

## Notes & TODOs
- Persistence: add save/load (JSON, SQLite or binary) if you want sessions to persist.
- Input validation: improve validation for numeric fields.
- Packaging: consider CMake to simplify cross-platform builds and dependency resolution.


## Author
- Repository: https://github.com/Dhruv00421/
