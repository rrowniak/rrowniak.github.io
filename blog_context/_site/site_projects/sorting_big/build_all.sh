#!/bin/bash

function fail() {
    echo "$1"
    exit 1
}

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

for lang in c cpp java go python; do
    echo "Building $lang version..."
    cd "$SCRIPT_DIR/$lang" || fail "Directory $SCRIPT_DIR/$lang does not exist"
    [ -f build.sh ] || fail "Build script not found."
    ./build.sh || fail "Build $lang sort falied"
    echo "   Done."
done