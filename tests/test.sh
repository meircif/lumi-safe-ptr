#!/bin/bash
set -ev

if [ -z $CXX ]; then
  CXX=g++
fi

if [ -z $CXXSTD ]; then
  CXXSTD=c++17
fi

CXXA="$CXX -std=$CXXSTD -Iinclude -fsyntax-only"

echo $CXXA

# success test
$CXXA tests/test.cpp

# missing check test
$CXXA -DMAKE_MISSING_CHECK tests/test.cpp 2>&1 | grep -Fq \
    "cycle check for strong pointer missing from 'LUMI_CYCLE_CHECK' macro"

# cycle error test
$CXXA -DMAKE_CYCLE_ERROR tests/test.cpp 2>&1 | \
    grep -Fq "cyclic reference detected in type"

# tests passed
