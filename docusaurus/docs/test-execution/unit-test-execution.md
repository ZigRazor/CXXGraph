---
id: unit-test-execution
title: 'Unit-Test Execution'
tags: ['benchmark execution', 'execution', 'testing', 'benchmark', 'googletest', 'install']
---
The Unit-Test requires [CMake](https://cmake.org/) 3.9 and later, and the [GoogleTest](https://github.com/google/googletest) library.

### Install Googletest
```
git clone https://github.com/google/googletest.git
cd googletest        # Main directory of the cloned repository
mkdir -p build       # Create a directory to hold the build output
cd build
cmake ..             # Generate native build scripts for GoogleTest
make                 # Compile
sudo make install    # Install in /usr/local/ by default
```

---
### How to compile Googletest

From the base directory:
```
mkdir -p build       # Create a directory to hold the build output
cd build             # Enter the build folder
cmake -DTEST=ON ..   # Generate native build scripts for GoogleTest,
make                 # Compile

```

---
### How to run Googletest

After the build has compiled, run the “test_exe” executable in the “build” directory with the following command:
`
./test_exe
`
