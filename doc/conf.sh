#!/bin/bash

# Possible arguments:
#
# -DBOOST_ROOT=/path/to/boost
#
#     Path to root of boost installation. This is a directory that contains
#     directories 'boost', 'libs' and file 'bootstrap.sh'.
#
# -DBOOST_LIBRARYDIR=/path/to/boost/libraries
#
#     Path to directory with boost libraries. When boost is built in-tree,
#     this is directory <boost-root>/stage/libs.

cmake -G "Unix Makefiles" ..
