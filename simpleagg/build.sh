#!/bin/sh

GTEST_INCLUDE_DIR=/scratch/gtest-1.7.0/include
GTEST_LIB_DIR=/scratch/gtest-1.7.0/build

CXX=c++
CXX_FLAGS="-g -Wall -Wextra -O3 -std=c++11"

$CXX $CXX_FLAGS  simpleagg.cpp -o simpleagg.exe
$CXX $CXX_FLAGS groupby.cpp -o groupby.exe
