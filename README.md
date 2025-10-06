![status.badge] [![language.badge]][language.url] [![standard.badge]][standard.url]

# openplan

openplan is a C++ library and XML-based file format for describing building structure — rooms, walls, floors, doors, and devices — for use in home automation, simulation, and visualization. it is compatible with open street map [simple indoor tagging](https://wiki.openstreetmap.org/wiki/Simple_Indoor_Tagging)

## Prerequisites

To build the project, you need:

- A C++17 compiler (e.g. `g++` or `clang++`)
- CMake 3.10 or newer
- `pkg-config`
- Cairo development libraries (for drawing floor plans)
- Git (to fetch dependencies)

On Debian/Ubuntu, install dependencies with:

```bash
sudo apt install build-essential cmake pkg-config libcairo2-dev
```

## Build instructions

Clone the repository and build using CMake:

```bash
git clone https://github.com/your-username/openplan.git
cd openplan
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

This will:

- Build the core openplan_lib library
- Build the openplan main program (if present)
- Build and run the unit tests using Google Test

To run tests:

```bash
cd build
ctest
```

## Output formats

The library can render floor plans using Cairo to various formats:

- PNG (bitmap image)
- PDF
- SVG
- PostScript

## License

This project is licensed under the [MIT License](LICENSE).

## Copyright

© 2025 Tomaz Stih. All rights reserved.

[language.url]: https://isocpp.org/
[language.badge]: https://img.shields.io/badge/language-C++-blue.svg
[standard.url]: https://en.wikipedia.org/wiki/C%2B%2B#Standardization
[standard.badge]: https://img.shields.io/badge/C%2B%2B-20-blue.svg
[status.badge]: https://img.shields.io/badge/status-unstable-red.svg
