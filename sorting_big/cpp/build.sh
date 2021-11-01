#!/bin/bash

rm -f sort sort_debug

gcc -std=c++11 -O3 sort.cpp -o sort -lstdc++ || exit 1
gcc -std=c++11 -g sort.cpp -o sort_debug -lstdc++ || exit 1
