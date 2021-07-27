#!/bin/bash

#Clean
./clean_rpm.sh

#Prepare Directories

mkdir BUILD
mkdir RPMS
mkdir SOURCES
mkdir SRPMS

#Build RPMs

rpmbuild -ba SPECS/CXXGraph.spec