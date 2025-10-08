& {
  $curr_folder = Split-Path -Path $pwd -Leaf
  if ($curr_folder -eq "custom-errors") {
    cd tests
  } elseif ($curr_folder -ne "tests") {
    write-host "Please set the directory to 'tests'!"
    exit
  }
}

if (!(test-path -path exe)) {
  mkdir exe
}

cl /Od /Wall ../src/custom_errors.c test.c /Fe: exe/c_test /std:c17
cl /Od /Wall /EHsc ../src/custom_errors.c test.cpp /Fe: exe/cpp_test /std:c++20

./exe/c_test
./exe/cpp_test

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

  cl /O2 /FA macro_test.cpp $with_defines
  rename-item -path macro_test.asm -newname $to_be
  move-item -path $to_be -destination $at

}

see_assembly -to_be none.asm -at basic -with_defines ""
see_assembly -to_be ndebug.asm -at basic -with_defines "/DNDEBUG"
see_assembly -to_be assume.asm -at basic -with_defines "/DCE_ASSUME_ALL"
see_assembly -to_be jumbo.asm -at basic -with_defines "/DCE_NO_WARN /DCE_ASSUME_WARN /DNDEBUG /DCE_ASSUME_ALL"

see_assembly -to_be now.asm -at no -with_defines "/DCE_NO_WARN"
see_assembly -to_be noe.asm -at no -with_defines "/DCE_NO_ERROR"
see_assembly -to_be nof.asm -at no -with_defines "/DCE_NO_FATAL"
see_assembly -to_be nowe.asm -at no -with_defines "/DCE_NO_WARN /DCE_NO_ERROR"
see_assembly -to_be nowf.asm -at no -with_defines "/DCE_NO_WARN /DCE_NO_FATAL"
see_assembly -to_be noef.asm -at no -with_defines "/DCE_NO_ERROR /DCE_NO_FATAL"
see_assembly -to_be nowef.asm -at no -with_defines "/DCE_NO_WARN /DCE_NO_ERROR /DCE_NO_FATAL"

see_assembly -to_be asw.asm -at assume -with_defines "/DCE_ASSUME_WARN"
see_assembly -to_be ase.asm -at assume -with_defines "/DCE_ASSUME_ERR0R"
see_assembly -to_be asf.asm -at assume -with_defines "/DCE_ASSUME_FATAL"
see_assembly -to_be aswe.asm -at assume -with_defines "/DCE_ASSUME_WARN /DCE_ASSUME_ERROR"
see_assembly -to_be aswf.asm -at assume -with_defines "/DCE_ASSUME_WARN /DCE_ASSUME_FATAL"
see_assembly -to_be asef.asm -at assume -with_defines "/DCE_ASSUME_ERROR /DCE_ASSUME_FATAL"
see_assembly -to_be aswef.asm -at assume -with_defines "/DCE_ASSUME_WARN /DCE_ASSUME_ERROR /DCE_ASSUME_FATAL"

see_assembly -to_be nwae.asm -at combo -with_defines "/DCE_NO_WARN /DCE_ASSUME_ERROR"
see_assembly -to_be nwaf.asm -at combo -with_defines "/DCE_NO_WARN /DCE_ASSUME_FATAL"
see_assembly -to_be nwaef.asm -at combo -with_defines "/DCE_NO_ERROR /DCE_ASSUME_WARN /DCE_ASSUME_FATAL"
see_assembly -to_be neaw.asm -at combo -with_defines "/DCE_NO_ERROR /DCE_ASSUME_WARN"
see_assembly -to_be neaf.asm -at combo -with_defines "/DCE_NO_ERROR /DCE_ASSUME_FATAL"
see_assembly -to_be neawf.asm -at combo -with_defines "/DCE_NO_ERROR /DCE_ASSUME_WARN /DCE_ASSUME_FATAL"
see_assembly -to_be nfae.asm -at combo -with_defines "/DCE_NO_FATAL /DCE_ASSUME_ERROR"
see_assembly -to_be nfaw.asm -at combo -with_defines "/DCE_NO_FATAL /DCE_ASSUME_WARN /DCE_ASSUME_ERROR"
see_assembly -to_be nfawe.asm -at combo -with_defines "/DCE_NO_FATAL /DCE_ASSUME_WARN"

rm macro_test.obj
rm custom_errors.obj
rm test.obj
