cmake_minimum_required(VERSION 3.20)
project(custom_errors)

# # Generate compile_commands.json if needed
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(BUILD_CUSTOM_ERRORS_LIBRARY OR NOT PROJECT_IS_TOP_LEVEL)

  # Build as library
  # You can include errors.c and errors.h directly into project if needed
  add_library(custom_errors STATIC src/custom_errors.c)

else() # when PROJECT_IS_TOP_LEVEL

  # Build tests
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY exe)

  add_executable(cpp_test src/custom_errors.c tests/test.cpp)
  target_compile_features(cpp_test PRIVATE cxx_std_17)

  add_executable(c_test src/custom_errors.c tests/test.c)
  target_compile_features(c_test PRIVATE c_std_17)

endif()
