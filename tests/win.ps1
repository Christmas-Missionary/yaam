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

$set_of_defines = @{
  0 = ""
  1 = "/DNDEBUG"
  2 = "/DCE_ASSUME_ALL"
  3 = "/DCE_NO_WARN /DCE_ASSUME_WARN /DNDEBUG /DCE_ASSUME_ALL"
  4 = "/DCE_NO_WARN"
  5 = "/DCE_NO_ERROR"
  6 = "/DCE_NO_FATAL"
  7 = "/DCE_NO_WARN /DCE_NO_ERROR"
  8 = "/DCE_NO_WARN /DCE_NO_FATAL"
  9 = "/DCE_NO_ERROR /DCE_NO_FATAL"
  10 = "/DCE_NO_WARN /DCE_NO_ERROR /DCE_NO_FATAL"
  11 = "/DCE_ASSUME_WARN"
  12 = "/DCE_ASSUME_ERROR"
  13 = "/DDCE_ASSUME_FATAL"
  14 = "/DCE_ASSUME_WARN /DCE_ASSUME_ERROR"
  15 = "/DCE_ASSUME_WARN /DCE_ASSUME_FATAL"
  16 = "/DCE_ASSUME_ERROR /DCE_ASSUME_FATAL"
  17 = "/DCE_ASSUME_WARN /DCE_ASSUME_ERROR /DCE_ASSUME_FATAL"
  18 = "/DCE_NO_WARN /DCE_ASSUME_ERROR"
  19 = "/DCE_NO_WARN /DCE_ASSUME_FATAL"
  20 = "/DCE_NO_WARN /DCE_ASSUME_ERROR /DCE_ASSUME_FATAL"
  21 = "/DCE_NO_ERROR /DCE_ASSUME_WARN"
  22 = "/DCE_NO_ERROR /DCE_ASSUME_FATAL"
  23 = "/DCE_NO_ERROR /DCE_ASSUME_WARN /DCE_ASSUME_FATAL"
  24 = "/DCE_NO_FATAL /DCE_ASSUME_ERROR"
  25 = "/DCE_NO_FATAL /DCE_ASSUME_WARN /DCE_ASSUME_ERROR"
  26 = "/DCE_NO_FATAL /DCE_ASSUME_WARN"
}

function see_assembly {

  param(
    [ValidatePattern('[a-z].asm')][string]$to_be,
    [ValidateSet("assume", "basic", "combo", "no")][string]$at,
    [ValidateRange(0, 26)][int]$with_define_entry
  )

  cl /O2 /FA assume_test.cpp set_of_defines.$with_define_entry
  rename-item -path assume_test.asm -newname $to_be
  move-item -path $to_be -destination $at

}

# for ($i = 0; $i -le 26; $i++) {
#   see_assembly -to_be none.asm -at basic -with_define_entry $i
# }
