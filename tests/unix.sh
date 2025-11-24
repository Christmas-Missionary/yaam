#!/usr/bin/env bash

# Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License

if [ ${PWD##*/} = "custom-errors" ]; then
  cd tests
elif [ ${PWD##*/} != "tests" ]; then
  echo "Please set the directory to 'tests'!"
  exit
fi

if [ ! -d "exe" ]; then
  mkdir exe
fi

cc -g -Wall -Wextra -Wpedantic ../src/custom_errors.c test.c -o exe/c_test -std=c17
g++ -g -Wall -Wextra -Wpedantic ../src/custom_errors.c test.cpp -o exe/cpp_test -std=c++23

./exe/c_test
./exe/cpp_test

if [ ! -d "basic" ]; then
  mkdir basic
fi
if [ ! -d "no" ]; then
  mkdir no
fi
if [ ! -d "assume" ]; then
  mkdir assume
fi
if [ ! -d "combo" ]; then
  mkdir combo
fi

g++ macro_test.cpp -S -o basic/none.s -O3
g++ macro_test.cpp -S -o basic/ndebug.s -DNDEBUG -O3
g++ macro_test.cpp -S -o basic/assume.s -DCE_ASSUME_ALL -O3
g++ macro_test.cpp -S -o basic/jumbo.s -DCE_NO_WARN -DCE_ASSUME_WARN -DNDEBUG -DCE_ASSUME_ALL -O3

g++ macro_test.cpp -S -o no/now.s -DCE_NO_WARN -O3
g++ macro_test.cpp -S -o no/noe.s -DCE_NO_ERROR -O3
g++ macro_test.cpp -S -o no/nof.s -DCE_NO_FATAL -O3
g++ macro_test.cpp -S -o no/nowe.s -DCE_NO_WARN -DCE_NO_ERROR -O3
g++ macro_test.cpp -S -o no/nowf.s -DCE_NO_WARN -DCE_NO_FATAL -O3
g++ macro_test.cpp -S -o no/noef.s -DCE_NO_ERROR -DCE_NO_FATAL -O3
g++ macro_test.cpp -S -o no/nowef.s -DCE_NO_WARN -DCE_NO_ERROR -DCE_NO_FATAL -O3

g++ macro_test.cpp -S -o assume/asw.s -DCE_ASSUME_WARN -O3
g++ macro_test.cpp -S -o assume/ase.s -DCE_ASSUME_ERROR -O3
g++ macro_test.cpp -S -o assume/asf.s -DCE_ASSUME_FATAL -O3
g++ macro_test.cpp -S -o assume/aswe.s -DCE_ASSUME_WARN -DCE_ASSUME_ERROR -O3
g++ macro_test.cpp -S -o assume/aswf.s -DCE_ASSUME_WARN -DCE_ASSUME_FATAL -O3
g++ macro_test.cpp -S -o assume/asef.s -DCE_ASSUME_ERROR -DCE_ASSUME_FATAL -O3
g++ macro_test.cpp -S -o assume/aswef.s -DCE_ASSUME_WARN -DCE_ASSUME_ERROR -DCE_ASSUME_FATAL -O3

g++ macro_test.cpp -S -o combo/nwae.s -DCE_NO_WARN -DCE_ASSUME_ERROR -O3
g++ macro_test.cpp -S -o combo/nwaf.s -DCE_NO_WARN -DCE_ASSUME_FATAL -O3
g++ macro_test.cpp -S -o combo/nwaef.s -DCE_NO_WARN -DCE_ASSUME_ERROR -DCE_ASSUME_FATAL -O3
g++ macro_test.cpp -S -o combo/neaw.s -DCE_NO_ERROR -DCE_ASSUME_WARN -O3
g++ macro_test.cpp -S -o combo/neaf.s -DCE_NO_ERROR -DCE_ASSUME_FATAL -O3
g++ macro_test.cpp -S -o combo/neawf.s -DCE_NO_ERROR -DCE_ASSUME_WARN -DCE_ASSUME_FATAL -O3
g++ macro_test.cpp -S -o combo/nfae.s -DCE_NO_FATAL -DCE_ASSUME_ERROR -O3
g++ macro_test.cpp -S -o combo/nfaw.s -DCE_NO_FATAL -DCE_ASSUME_WARN -O3
g++ macro_test.cpp -S -o combo/nfawe.s -DCE_NO_FATAL -DCE_ASSUME_WARN -DCE_ASSUME_ERROR -O3
