#!/bin/bash

OPT_FLAG=O3
COMMON_FLAGS="-Wall -Wextra -pedantic -std=c++11"

for OPT_FLAG in "" "O2" "O3"
do
    if [ "x${OPT_FLAG}" == "x" ]; then
        OPT=""
    else
        OPT="-${OPT_FLAG}"
    fi

    gcc ${COMMON_FLAGS} ${OPT} vect_vs_set.cpp -o vect_vs_set${OPT_FLAG} -lstdc++ -DOPT_FLAG=\"${OPT_FLAG}\"

    if [ $? -ne 0 ]; then
        echo "Compilation error, abording build process"
        exit 1
    fi
done
