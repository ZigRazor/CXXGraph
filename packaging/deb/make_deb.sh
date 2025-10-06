#!/bin/bash

#Clean
./clean_deb.sh

#Prepare
mkdir -p CXXGraph/usr/include/
chmod -R 0755 CXXGraph/DEBIAN
cp -r ../../include/* CXXGraph/usr/include/

#Packaging
dpkg-deb --build CXXGraph

#Rename
mv CXXGraph.deb "CXXGraph_$VERSION-$RELEASE.deb"