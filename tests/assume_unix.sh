#!/usr/bin/env bash

g++ assume_test.cpp -S -o ndebug.s -DNDEBUG -O3
g++ assume_test.cpp -S -o assume.s -DCE_ASSUME_ALL -O3
echo "assume.s should be much shorter than ndebug.s."
