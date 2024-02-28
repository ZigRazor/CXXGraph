---
id: installation
title: 'Installing and Uninstalling'
tags: ['install', 'uninstall', 'getting started', 'requirements']
---
### Prerequesites
- The minimum C++ standard required is C++17
- A GCC compiler version 7.3.0 and later OR a MSVC compiler that supports C++17

---
### Install Linux Tarballs

To install on Unix/Linux systems, execute the following from the command line:
```
$ sudo tar xjf CXXGraph-{version}.tar.bz2
```
To uninstall:
```
$ sudo rm -f /usr/include/Graph.hpp /usr/include/CXXGraph*
```
---
### Install RPM

To install on Fedora/CentOS/RedHat systems, execute the following from the command line:
```
$ sudo rpm -ivh CXXGraph-{version}.noarch.rpm
```
To uninstall:
```
$ sudo rpm -e CXXGraph-{version}
```
 ---
### Install DEB

To install on Debian/Ubuntu systems, execute the following from the command line:
```
$ sudo dpkg -i CXXGraph_{version}.deb
```
To uninstall:
```
$ sudo apt-get remove CXXGraph
```
---
### Install From Source

For self-compiled installations using CMake, execute the following from the command line once compilation is complete:
```
$ sudo make install
```