---
sidebar_position: 5
---

The Unit-Test requires the CMake version greater than 3.9 and the **google test**  library.

### OpenSSL installation

[OpenSSL](https://www.openssl.org/)

#### Ubuntu/Debian

``` bash
sudo apt-get install openssl libssl-dev
```

#### RedHat/CentOS/RockyLinux/Fedora

``` bash
yum install openssl-devel
```

#### Other System

You can find more information on how to install OpenSSL at this [link](https://github.com/openssl/openssl)

### Google Test Installation

[GoogleTest](https://github.com/google/googletest)

```bash
git clone https://github.com/google/googletest.git
cd googletest        # Main directory of the cloned repository.
mkdir -p build       # Create a directory to hold the build output.
cd build
cmake ..             # Generate native build scripts for GoogleTest.
make                 # Compile
sudo make install    # Install in /usr/local/ by default
```

### How to Compile Test

From the base directory:

```bash
mkdir -p build       # Create a directory to hold the build output.
cd build             # Enter the build folder
cmake ..             # Generate native build scripts for GoogleTest.
make                 # Compile
```

### How to Run Test

After the compilation, you can run the executable that is under the "build" directory with the name "test_exe", with the simple command `./test_exe`.

## Benchmark Execution

The Benchmark required the CMake version greater than 3.9 and the **google test** and the **google benchmark** library.

### Google Benchmark Installation

[Google Benchmark](https://github.com/google/benchmark)

```bash
# Check out the library.
$ git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest
# Go to the library root directory
$ cd benchmark
# Make a build directory to place the build output.
$ cmake -E make_directory "build"
# Generate build system files with cmake.
$ cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
# or, starting with CMake 3.13, use a simpler form:
# cmake -DCMAKE_BUILD_TYPE=Release -S . -B "build"
# Build the library.
$ cmake --build "build" --config Release
# install library
$ sudo cmake --build "build" --config Release --target install
```

### How to Compile Benchmark

From the base directory:

```bash
mkdir -p build             # Create a directory to hold the build output.
cd build                   # Enter the build folder
cmake -DBENCHMARK=ON ..    # Generate native build scripts for GoogleTest.
make                       # Compile
```

### How to Run Benchmark

After the compilation, you can run the executable that is under the "build" directory with the name "benchmark", with the simple command `./benchmark`.

### Benchmark Results

You can check benchmark result at this [link](https://zigrazor.github.io/CXXGraph/dev/bench/)

## Packaging

### Tarballs

To create tarballs package you need to follow the following steps:

```bash
# Enter Packaging Directory
$ cd packaging
# execute the script to generate tarballs
$ ./tarballs.sh
```