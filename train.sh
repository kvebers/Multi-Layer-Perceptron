#!/usr/bin/env bash

if [ ! -f "exec" ]; then
    make
fi

./exec asd pre asd
if (( $? != 0 )); then
    exit 1
fi

cd visuals && python3 -m venv venv && source venv/bin/activate && pip install -r requirements.txt && python3 visuals.py