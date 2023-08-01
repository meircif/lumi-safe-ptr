#!/bin/bash

result=0

for cxx in g++ clang++
do
  for std in c++17 c++20
  do
    echo
    echo "---< run tests using compiler $cxx and standard $std >---"
    CXX=$cxx CXXSTD=$std tests/test.sh || result=1
  done
done

echo
if ((result)); then
    echo "--< some tests failed >--"
else
    echo "--< all tests passed >--"
fi
exit $result
