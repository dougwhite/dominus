# Dominus Lang

A powerful data driven scripting language inspired by Actian OpenROAD.

## Normal GCC debug build

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## Clang build

```
cmake -S . -B build-clang \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_COMPILER=clang++

cmake --build build-clang
ctest --test-dir build-clang --output-on-failure
```

## Sanitizer build

```
cmake -S . -B build-sanitize \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DDOMINUS_ENABLE_SANITIZERS=ON

cmake --build build-sanitize
ctest --test-dir build-sanitize --output-on-failure
```

## Disable warnings as errors temporarily

```
cmake -S . -B build \
    -DDOMINUS_WARNINGS_AS_ERRORS=OFF
```
