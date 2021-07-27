#!/bin/bash

tar --transform='flags=r;s|include/|/usr/include/|' -cvjSf   CXXGraph-$VERSION-$RELEASE.tar.bz2  ../include/*