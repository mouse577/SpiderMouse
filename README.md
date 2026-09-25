# SpiderMouse: Mouse, Experiment, and Project Data Structure

A C++ data-structures project for representing relationships among laboratory mice, their experiments, and research projects that use those experiments.

One mouse can have multiple experiments, and a project can reference selected experiments. The `SpiderMouse` class stores nodes and navigates these associations using vectors of `std::shared_ptr` objects. The repository includes an interactive command-line program and C++ tests.

## Data model

| Node | Relationship |
| --- | --- |
| Mouse | Holds references to experiments performed on that mouse |
| Experiment | Belongs to a mouse and can reference projects |
| Project | Holds references to associated experiments |

The implementation uses a common `spiderNode` structure with a `nodeType` field for mouse, experiment, or project. It is a graph-like object model rather than a database or a general-purpose graph library.

## Source guide

- [`SpiderMouse.h`](data-structures-project/term-project-neoygaj/code_1/SpiderMouse.h) defines the node structure and public operations.
- [`SpiderMouse.cpp`](data-structures-project/term-project-neoygaj/code_1/SpiderMouse.cpp) implements creation, lookup, association, removal, and display operations.
- [`main_1.cpp`](data-structures-project/term-project-neoygaj/app_1/main_1.cpp) starts the interactive program.
- [`test_SpiderMouse.cpp`](data-structures-project/term-project-neoygaj/tests/test_SpiderMouse.cpp) contains tests.
- The [original project write-up](data-structures-project/term-project-neoygaj/readme.md) explains the assignment and design in more detail.

## Build status

The project includes CMake configuration and an older `build/` directory. The current `CMakeLists.txt` looks for sources in `code/`, while the checked-in implementation is under `code_1/`. Correct that path in CMake before using a fresh build. The checked-in build artifacts are environment-specific and should not be treated as a portable executable.

After correcting the source path, configure a clean build from `data-structures-project/term-project-neoygaj/` with CMake and run the resulting application and tests. The CMake configuration uses C++11 and GoogleTest; if GoogleTest is not installed locally, it attempts to download it during configuration.
