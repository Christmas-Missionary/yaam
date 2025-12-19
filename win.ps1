# Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License

if (!(test-path -path tests)) {
  echo "Please go to the top directory of this repo!"
  exit
}

cd tests

if (!(test-path -path exe)) {
  mkdir exe
}

cl /Od /Wall ../src/yaam.c main.c /Fe: exe/c11_reg /std:c11 /DREG_ERROR_TEST
cl /Od /Wall ../src/yaam.c main.c /Fe: exe/c17_fatal /std:c17 /DFATAL_ERROR_TEST
cl /Od /Wall /TP /EHsc ../src/yaam.c main.c /Fe: exe/cpp14_reg /std:c++14 /DREG_ERROR_TEST
cl /Od /Wall /TP ../src/yaam.c main.c /Fe: exe/cpp17_fatal /std:c++17 /DFATAL_ERROR_TEST

./exe/c11_reg
./exe/c17_fatal
./exe/cpp14_reg
./exe/cpp17_fatal

if (!(test-path -path basic)) {
  mkdir basic
}
if (!(test-path -path no)) {
  mkdir no
}
if (!(test-path -path assume)) {
  mkdir assume
}
if (!(test-path -path combo)) {
  mkdir combo
}

function see_assembly {

  param(
    [ValidatePattern('[a-z].asm')][string]$to_be,
    [ValidateSet("assume", "basic", "combo", "no")][string]$at,
    [string]$with_defines
  )

  cl /O2 /FA main.c $with_defines
  rename-item -path main.asm -newname $to_be
  move-item -path $to_be -destination $at

}

see_assembly -to_be nodefs.asm -at basic -with_defines ""
see_assembly -to_be none.asm -at basic -with_defines "/DYAAM_NONE"
see_assembly -to_be assume.asm -at basic -with_defines "/DYAAM_ASSUME_ALL"
see_assembly -to_be jumbo.asm -at basic -with_defines "/DYAAM_NO_WARN /DYAAM_ASSUME_WARN /DYAAM_NONE /DYAAM_ASSUME_ALL"

see_assembly -to_be now.asm -at no -with_defines "/DYAAM_NO_WARN"
see_assembly -to_be noe.asm -at no -with_defines "/DYAAM_NO_ERROR"
see_assembly -to_be nof.asm -at no -with_defines "/DYAAM_NO_FATAL"
see_assembly -to_be nowe.asm -at no -with_defines "/DYAAM_NO_WARN /DYAAM_NO_ERROR"
see_assembly -to_be nowf.asm -at no -with_defines "/DYAAM_NO_WARN /DYAAM_NO_FATAL"
see_assembly -to_be noef.asm -at no -with_defines "/DYAAM_NO_ERROR /DYAAM_NO_FATAL"
see_assembly -to_be nowef.asm -at no -with_defines "/DYAAM_NO_WARN /DYAAM_NO_ERROR /DYAAM_NO_FATAL"

see_assembly -to_be asw.asm -at assume -with_defines "/DYAAM_ASSUME_WARN"
see_assembly -to_be ase.asm -at assume -with_defines "/DYAAM_ASSUME_ERR0R"
see_assembly -to_be asf.asm -at assume -with_defines "/DYAAM_ASSUME_FATAL"
see_assembly -to_be aswe.asm -at assume -with_defines "/DYAAM_ASSUME_WARN /DYAAM_ASSUME_ERROR"
see_assembly -to_be aswf.asm -at assume -with_defines "/DYAAM_ASSUME_WARN /DYAAM_ASSUME_FATAL"
see_assembly -to_be asef.asm -at assume -with_defines "/DYAAM_ASSUME_ERROR /DYAAM_ASSUME_FATAL"
see_assembly -to_be aswef.asm -at assume -with_defines "/DYAAM_ASSUME_WARN /DYAAM_ASSUME_ERROR /DYAAM_ASSUME_FATAL"

see_assembly -to_be nwae.asm -at combo -with_defines "/DYAAM_NO_WARN /DYAAM_ASSUME_ERROR"
see_assembly -to_be nwaf.asm -at combo -with_defines "/DYAAM_NO_WARN /DYAAM_ASSUME_FATAL"
see_assembly -to_be nwaef.asm -at combo -with_defines "/DYAAM_NO_ERROR /DYAAM_ASSUME_WARN /DYAAM_ASSUME_FATAL"
see_assembly -to_be neaw.asm -at combo -with_defines "/DYAAM_NO_ERROR /DYAAM_ASSUME_WARN"
see_assembly -to_be neaf.asm -at combo -with_defines "/DYAAM_NO_ERROR /DYAAM_ASSUME_FATAL"
see_assembly -to_be neawf.asm -at combo -with_defines "/DYAAM_NO_ERROR /DYAAM_ASSUME_WARN /DYAAM_ASSUME_FATAL"
see_assembly -to_be nfae.asm -at combo -with_defines "/DYAAM_NO_FATAL /DYAAM_ASSUME_ERROR"
see_assembly -to_be nfaw.asm -at combo -with_defines "/DYAAM_NO_FATAL /DYAAM_ASSUME_WARN /DYAAM_ASSUME_ERROR"
see_assembly -to_be nfawe.asm -at combo -with_defines "/DYAAM_NO_FATAL /DYAAM_ASSUME_WARN"

rm main.obj
rm yaam.obj
cd ..
