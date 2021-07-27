#!/bin/bash

#variables
MAJOR=$(cat ../include/CXXGraphConfig.h | grep CXXGraph_VERSION_MAJOR | awk '{ print $3 }')
MINOR=$(cat ../include/CXXGraphConfig.h | grep CXXGraph_VERSION_MINOR | awk '{ print $3 }')
PATCH=$(cat ../include/CXXGraphConfig.h | grep CXXGraph_VERSION_PATCH | awk '{ print $3 }')

echo "Packaging version $MAJOR.$MINOR.$PATCH"

export VERSION=${MAJOR}.${MINOR}
export RELEASE=${PATCH}

#tarballs
echo "Create Tarballs..."
./tarballs.sh
echo "Tarballs Created"

#rpm
echo "Create RPM..."
cd rpm
./make_rpm.sh
cd ..
echo "RPM Created"

echo "Create DEB..."
#deb
cd deb
./make_deb.sh
cd ..
echo "DEB Created"
