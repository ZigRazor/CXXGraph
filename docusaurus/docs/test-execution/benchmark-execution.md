---
id: benchmark-execution
title: 'Benchmark Execution'
tags: ['benchmark execution', 'execution', 'testing', 'benchmark', 'googletest',]
---
Benchmark requires [CMake](https://cmake.org/) 3.9 and later, the [GoogleTest](https://github.com/google/googletest) library, and the [Google Benchmark](https://github.com/google/benchmark) library.

### Install Google Benchmark

```
# Check out the library
$ git clone https://github.com/google/benchmark.git
# Google Benchmark requires GoogleTest as a dependency.
# Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest
# Go to the library's root directory
$ cd benchmark
# Make a build directory to place the build output
$ cmake -E make_directory "build"
# Generate the build system files with CMake
$ cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
# If starting with CMake 3.13, you can use the following:
# cmake -DCMAKE_BUILD_TYPE=Release -S . -B "build"
# Build the library
$ cmake --build "build" --config Release
# Install the library
$ sudo cmake --build "build" --config Release --target install
```

---
### How to compile Google Benchmark
From the base directory:
```
mkdir -p build             # Create a directory to hold the build output
cd build                   # Enter the build folder
cmake -DBENCHMARK=ON ..    # Generate native build scripts for Google Benchmark
make                       # Compile
```

---
### How to run Google Benchmark
After the build has compiled, run the “benchmark” executable in the “build” directory with the following command:

`
./benchmark
`

---
### Benchmark Results
You can check the benchmark result using this [link](https://zigrazor.github.io/CXXGraph/dev/bench/).