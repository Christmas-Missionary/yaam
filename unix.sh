#!/usr/bin/env bash

# Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License

if [ ! -d "tests" ]; then
  echo "Please go to the top directory of this repo!"
  exit
fi
cd tests

if [ ! -d "exe" ]; then
  mkdir exe
fi

# -ansi # Soon...
cc -g -Wall -Wextra -Wpedantic ../src/custom_errors.c main.c -o exe/reg_test -std=c99 -DREG_ERROR_TEST
cc -g -Wall -Wextra -Wpedantic ../src/custom_errors.c main.c -o exe/fatal_test -std=c99 -DFATAL_ERROR_TEST

./exe/reg_test
./exe/fatal_test

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

cc main.c -S -o basic/nodefs.s -O3
cc main.c -S -o basic/none.s -DCE_NONE -O3
cc main.c -S -o basic/assume.s -DCE_ASSUME_ALL -O3
cc main.c -S -o basic/jumbo.s -DCE_NO_WARN -DCE_ASSUME_WARN -DCE_NONE -DCE_ASSUME_ALL -O3

cc main.c -S -o no/now.s -DCE_NO_WARN -O3
cc main.c -S -o no/noe.s -DCE_NO_ERROR -O3
cc main.c -S -o no/nof.s -DCE_NO_FATAL -O3
cc main.c -S -o no/nowe.s -DCE_NO_WARN -DCE_NO_ERROR -O3
cc main.c -S -o no/nowf.s -DCE_NO_WARN -DCE_NO_FATAL -O3
cc main.c -S -o no/noef.s -DCE_NO_ERROR -DCE_NO_FATAL -O3
cc main.c -S -o no/nowef.s -DCE_NO_WARN -DCE_NO_ERROR -DCE_NO_FATAL -O3

cc main.c -S -o assume/asw.s -DCE_ASSUME_WARN -O3
cc main.c -S -o assume/ase.s -DCE_ASSUME_ERROR -O3
cc main.c -S -o assume/asf.s -DCE_ASSUME_FATAL -O3
cc main.c -S -o assume/aswe.s -DCE_ASSUME_WARN -DCE_ASSUME_ERROR -O3
cc main.c -S -o assume/aswf.s -DCE_ASSUME_WARN -DCE_ASSUME_FATAL -O3
cc main.c -S -o assume/asef.s -DCE_ASSUME_ERROR -DCE_ASSUME_FATAL -O3
cc main.c -S -o assume/aswef.s -DCE_ASSUME_WARN -DCE_ASSUME_ERROR -DCE_ASSUME_FATAL -O3

cc main.c -S -o combo/nwae.s -DCE_NO_WARN -DCE_ASSUME_ERROR -O3
cc main.c -S -o combo/nwaf.s -DCE_NO_WARN -DCE_ASSUME_FATAL -O3
cc main.c -S -o combo/nwaef.s -DCE_NO_WARN -DCE_ASSUME_ERROR -DCE_ASSUME_FATAL -O3
cc main.c -S -o combo/neaw.s -DCE_NO_ERROR -DCE_ASSUME_WARN -O3
cc main.c -S -o combo/neaf.s -DCE_NO_ERROR -DCE_ASSUME_FATAL -O3
cc main.c -S -o combo/neawf.s -DCE_NO_ERROR -DCE_ASSUME_WARN -DCE_ASSUME_FATAL -O3
cc main.c -S -o combo/nfae.s -DCE_NO_FATAL -DCE_ASSUME_ERROR -O3
cc main.c -S -o combo/nfaw.s -DCE_NO_FATAL -DCE_ASSUME_WARN -O3
cc main.c -S -o combo/nfawe.s -DCE_NO_FATAL -DCE_ASSUME_WARN -DCE_ASSUME_ERROR -O3
