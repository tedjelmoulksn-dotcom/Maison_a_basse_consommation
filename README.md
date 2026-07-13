# Maison à Basse Consommation

A C++ project to model and simulate a low-energy house (Maison à Basse Consommation — MBC). This repository contains the source code, example configurations, and build scripts to run thermal and energy-consumption simulations for a residential building.

> Project name is in French; the README is written in English for broader accessibility. If you prefer French, I can provide a translated version.

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Repository structure](#repository-structure)
- [Prerequisites](#prerequisites)
- [Build](#build)
- [Run](#run)
- [Configuration & Examples](#configuration--examples)
- [Testing](#testing)
- [Contributing](#contributing)
- [Roadmap](#roadmap)
- [License](#license)
- [Contact](#contact)

---

## About

Maison à Basse Consommation (MBC) is a C++ simulation project focused on modelling the thermal behaviour and energy use of a single-family house. It can be used for:

- Evaluating insulation and glazing options
- Comparing HVAC strategies
- Producing time-series outputs for further analysis and plotting

## Features

- Modular C++ codebase for thermal and energy models
- Configurable building parameters (envelope, windows, HVAC, occupancy)
- Exportable CSV/JSON results
- Example scenarios to reproduce typical seasonal cases

## Repository structure

- `src/` — C++ sources
- `include/` — public headers (if present)
- `examples/` — configuration files and example inputs
- `build/` — out-of-source build directory (not committed)
- `tests/` — unit and integration tests
- `tools/` — helper scripts (plotting, data conversion)
- `CMakeLists.txt` — CMake build configuration
- `README.md` — this file

Update the above if your repository uses a different layout.

## Prerequisites

- C++17-capable compiler (GCC >= 9, Clang >= 10, MSVC with C++17 support)
- CMake >= 3.10 (recommended)
- Optional: Python 3 and matplotlib for plotting results

## Build

Using CMake (recommended):

```bash
# from repository root
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Simple single-file build (if the project is small):

```bash
g++ -std=c++17 -O2 -Wall -Iinclude -o mbc_sim src/main.cpp
```

The produced executable is typically placed in `build/` or the project root depending on your build system.

## Run

Basic usage (replace `mbc_sim` and paths with actual names used in your project):

```bash
./build/mbc_sim --config ../examples/winter_case.json --output results/winter.csv
```

Example: generate results and plot with Python

```bash
python3 tools/plot_results.py results/winter.csv
```

Document the available command-line options or config file schema in `docs/` or in `examples/`.

## Configuration & Examples

Place JSON/YAML configuration files in `examples/` describing:

- Building geometry and areas
- Construction layers and U-values
- Window areas and solar gains
- Internal gains and occupancy schedules
- HVAC setpoints and efficiencies

Provide at least two example scenarios (winter / summer) to help users validate the model.

## Testing

If tests are provided (recommended), build and run them with CTest:

```bash
cd build
ctest --output-on-failure
```

Or run the test executable directly:

```bash
./tests/run_tests
```

Include unit tests for numerical components and regression tests for whole-case scenarios.

## Contributing

Contributions are welcome. Suggested workflow:

1. Fork the repository.
2. Create a branch: `git checkout -b feat/your-feature`.
3. Add tests for your changes.
4. Run the test suite and ensure all checks pass.
5. Open a pull request with a clear description and motivation.

Please follow a consistent code style (e.g., clang-format) and add or update documentation when public APIs change.

## Roadmap

- Add continuous integration (GitHub Actions) for build and tests
- Improve documentation and add an `API.md` for core modules
- Add more example scenarios and visualization tools

## License

Add a `LICENSE` file to this repository to indicate the license you want to use (e.g., MIT, Apache-2.0). If there is no license file, all rights are reserved by default.

## Contact

Maintainer: tedjelmoulksn-dotcom

---

Notes:
- I updated README.md with a professional, actionable template. If you'd like, I can also:
  - Translate this README to French,
  - Add badges (build status, license) with working links,
  - Create CONTRIBUTING.md and a GitHub Actions workflow for CI.
