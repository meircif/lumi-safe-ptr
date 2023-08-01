#!/bin/bash
set -ev

if [ -z $CXX ]; then
  CXX=g++
fi

CXXA="$CXX -Iinclude -fsyntax-only"

# success test
$CXXA tests/test.cpp

# missing check test
$CXXA -DMAKE_MISSING_CHECK tests/test.cpp 2>&1 | grep -Fq \
    "cycle check for strong pointer missing from 'LUMI_CYCLE_CHECK' macro"

# cycle error test
$CXXA -DMAKE_CYCLE_ERROR tests/test.cpp 2>&1 | \
    grep -Fq "cyclic reference detected in type"

# All tests passed
