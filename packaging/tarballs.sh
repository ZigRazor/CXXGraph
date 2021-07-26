#!/bin/bash

tar --transform='flags=r;s|include/|/usr/include/|' -cvjSf   CXXGraph.tar.bz2  ../include/*