#!/usr/bin/env bash

if [ ! -f "exec" ]; then
    make
fi

./exec asd asd pre
if (( $? != 0 )); then
    exit 1
fi