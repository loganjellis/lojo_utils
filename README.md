# lojo_utils

lojo_utils is a collection of utility functions and libraries written in C.

## Clone the repository

```
git clone https://github.com/loganjellis/lojo_utils.git
cd lojo_utils
```

## Building

```
cmake -S . -B build
cmake --build build
```

## Optionally installing

```
cmake --install build --prefix ./install
```

> [!NOTE]
> Note that ./install is a placeholder install location for the library. Omitting the install location results in the library being installed in the operating system's default path.

### Using the library (installed package)

```
list(APPEND CMAKE_PREFIX_PATH "/path/to/lojo_utils/install")
find_package(LOJO_UTILS REQUIRED)
target_link_libraries(app PRIVATE LOJO_UTILS::lojo_utils)
```

### Using the library (subdirectory)

```
add_subdirectory(LOJO_UTILS)
target_link_libraries(app PRIVATE LOJO_UTILS::lojo_utils)
```

For an example of using the library, refer to `example.c`

To view the library's documentation, click <a href="docs/html" target="_blank">here</a>.
