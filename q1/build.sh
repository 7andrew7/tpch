#!/bin/sh

GTEST_INCLUDE_DIR=/scratch/gtest-1.7.0/include
GTEST_LIB_DIR=/scratch/gtest-1.7.0/build

CXX=c++
CXX_FLAGS="-g -Wall -Wextra -std=c++11"

$CXX $CXX_FLAGS  -c q1.cpp
$CXX $CXX_FLAGS -lbenchmark q1_perf.cpp -o q1_perf.exe
$CXX $CXX_FLAGS -I $GTEST_INCLUDE_DIR $GTEST_LIB_DIR/libgtest.a $GTEST_LIB_DIR/libgtest_main.a q1_test.cpp -o q1_test.exe
