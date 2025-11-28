# dsa

A repository with implementations for common Data Structures and Algorithms in C++.

This project includes:

- Implementations of standard algorithms and data structures under `src/`.
- Unit tests under `tests/` using GoogleTest.
- CMake build system to build and run unit tests.

## Quick start (building with CMake)

From the repository root:

```bash
# configure
cmake -B build -S . -G Ninja

# build
cmake --build build

# test
ctest --test-dir build --parallel
```

## License

This project is licensed under the terms in the `LICENSE` file.
