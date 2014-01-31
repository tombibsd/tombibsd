#!/bin/sh
# $NetBSD$
#
# Checkout compiler_rt into dist.
# Run this script and check for additional files and directories to prune,
# only relevant content should be included.

set -e

cd dist
rm -rf .svn
rm -rf BlocksRuntime SDKs cmake include make www
rm -f .arcconfig .gitignore CMakeLists.txt Makefile
rm -rf lib/asan lib/dfsan lib/interception lib/lsan lib/msan lib/msandr
rm -rf lib/sanitizer_common lib/tsan lib/ubsan
rm -f lib/*/Makefile.mk lib/Makefile.mk lib/CMakeLists.txt
rm -f lib/apple_versioning.c lib/lit.common.* lib/profile/CMakeLists.txt
