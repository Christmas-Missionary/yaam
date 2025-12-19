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

cc -g -Wall -Wextra -Wpedantic ../src/yaam.c main.c -o exe/c89_reg -std=c89 -DREG_ERROR_TEST
cc -g -Wall -Wextra -Wpedantic ../src/yaam.c main.c -o exe/c95_fatal -std=iso9899:199409 -DFATAL_ERROR_TEST
cc -g -Wall -Wextra -Wpedantic ../src/yaam.c main.c -o exe/c99_reg -std=c99 -DREG_ERROR_TEST
g++ -g -Wall -Wextra -Wpedantic ../src/yaam.c main.c -o exe/cpp98_reg -std=c++98 -DREG_ERROR_TEST
g++ -g -Wall -Wextra -Wpedantic ../src/yaam.c main.c -o exe/cpp11_fatal -std=c++11 -DFATAL_ERROR_TEST

./exe/c89_reg
./exe/c95_fatal
./exe/c99_reg
./exe/cpp98_reg
./exe/cpp11_fatal

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
cc main.c -S -o basic/none.s -DYAAM_NONE -O3
cc main.c -S -o basic/assume.s -DYAAM_ASSUME_ALL -O3
cc main.c -S -o basic/jumbo.s -DYAAM_NO_WARN -DYAAM_ASSUME_WARN -DYAAM_NONE -DYAAM_ASSUME_ALL -O3

cc main.c -S -o no/now.s -DYAAM_NO_WARN -O3
cc main.c -S -o no/noe.s -DYAAM_NO_ERROR -O3
cc main.c -S -o no/nof.s -DYAAM_NO_FATAL -O3
cc main.c -S -o no/nowe.s -DYAAM_NO_WARN -DYAAM_NO_ERROR -O3
cc main.c -S -o no/nowf.s -DYAAM_NO_WARN -DYAAM_NO_FATAL -O3
cc main.c -S -o no/noef.s -DYAAM_NO_ERROR -DYAAM_NO_FATAL -O3
cc main.c -S -o no/nowef.s -DYAAM_NO_WARN -DYAAM_NO_ERROR -DYAAM_NO_FATAL -O3

cc main.c -S -o assume/asw.s -DYAAM_ASSUME_WARN -O3
cc main.c -S -o assume/ase.s -DYAAM_ASSUME_ERROR -O3
cc main.c -S -o assume/asf.s -DYAAM_ASSUME_FATAL -O3
cc main.c -S -o assume/aswe.s -DYAAM_ASSUME_WARN -DYAAM_ASSUME_ERROR -O3
cc main.c -S -o assume/aswf.s -DYAAM_ASSUME_WARN -DYAAM_ASSUME_FATAL -O3
cc main.c -S -o assume/asef.s -DYAAM_ASSUME_ERROR -DYAAM_ASSUME_FATAL -O3
cc main.c -S -o assume/aswef.s -DYAAM_ASSUME_WARN -DYAAM_ASSUME_ERROR -DYAAM_ASSUME_FATAL -O3

cc main.c -S -o combo/nwae.s -DYAAM_NO_WARN -DYAAM_ASSUME_ERROR -O3
cc main.c -S -o combo/nwaf.s -DYAAM_NO_WARN -DYAAM_ASSUME_FATAL -O3
cc main.c -S -o combo/nwaef.s -DYAAM_NO_WARN -DYAAM_ASSUME_ERROR -DYAAM_ASSUME_FATAL -O3
cc main.c -S -o combo/neaw.s -DYAAM_NO_ERROR -DYAAM_ASSUME_WARN -O3
cc main.c -S -o combo/neaf.s -DYAAM_NO_ERROR -DYAAM_ASSUME_FATAL -O3
cc main.c -S -o combo/neawf.s -DYAAM_NO_ERROR -DYAAM_ASSUME_WARN -DYAAM_ASSUME_FATAL -O3
cc main.c -S -o combo/nfae.s -DYAAM_NO_FATAL -DYAAM_ASSUME_ERROR -O3
cc main.c -S -o combo/nfaw.s -DYAAM_NO_FATAL -DYAAM_ASSUME_WARN -O3
cc main.c -S -o combo/nfawe.s -DYAAM_NO_FATAL -DYAAM_ASSUME_WARN -DYAAM_ASSUME_ERROR -O3
