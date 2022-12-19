#!/bin/bash

rm -f sort sort_debug

gcc -Wall -O3  sort.c -o sort || exit 1
gcc -Wall -g sort.c -o sort_debug || exit 1
