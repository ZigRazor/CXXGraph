#!/bin/bash

#variables
MAJOR=$(grep CXXGraph_VERSION_MAJOR ../include/CXXGraphConfig.h | awk '{ print $3 }')
MINOR=$(grep CXXGraph_VERSION_MINOR ../include/CXXGraphConfig.h | awk '{ print $3 }')
PATCH=$(grep CXXGraph_VERSION_PATCH ../include/CXXGraphConfig.h | awk '{ print $3 }')

echo "Packaging version $MAJOR.$MINOR.$PATCH"

export VERSION=${MAJOR}.${MINOR}
export RELEASE=${PATCH}

#tarballs
echo "Create Tarballs..."
./tarballs.sh
echo "Tarballs Created"

#zip
echo "Create Zip..."
./zip.sh
echo "Zip Created"

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
