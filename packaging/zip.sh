#!/bin/bash
cd ../..
zip -r "CXXGraph/packaging/CXXGraph-$VERSION-$RELEASE.zip" CXXGraph/include/* CXXGraph/packaging/haxelib.json
cd -