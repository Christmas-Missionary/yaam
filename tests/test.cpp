// Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License

#define _LIBCPP_REMOVE_TRANSITIVE_INCLUDES

#include "../src/custom_errors.h"
#include <string>

static_assert(sizeof(char) == 1, "God has left us!");

// src - reference of source string -> new string on heap or a default init if failed
// Example: ("Cats", 5) -> "CATS"
static std::string all_caps(std::string const & src) {
  std::string res{};
  const std::string::size_type size = src.size();
  CE_WARN(size != 0, "No size for the string!");
  if (size == 0) {
    return res;
  }

  try {
    res.reserve(size);
  } catch (...) {
    CE_FATAL(false, "Couldn't malloc new string!");
    return res;
  }

  size_t index = 0;
  for (; index < size; index++) {
    const char chr = src[index];
    if (chr >= 'a' && chr <= 'z') {
      res.push_back(static_cast<char>(chr - 32));
      continue;
    }
    res.push_back(chr);
  }
  return res;
}

#include <array>
#include <iostream>

int main() {
#ifdef _WIN32
  if (set_windows_colors() != 0) {
    printf("Colored text output will not work on windows!\n");
  }
#endif
  constexpr long cpp_version = (
#ifdef _WIN32
    _MSVC_LANG
#else
    __cplusplus
#endif
  );
  std::cout << "C++ standard version: " << cpp_version << "\n";

  const std::array<std::string, 4> strs = {"Hello.", "123456789({[|]})`~QAZqazwebWEBJILLjill<>,.:;/?!@#$%^&*",
                                           "qwertyuiopasdfghjklzxcvbnm", "POIUYTREWQLKJHGFDSAMNBVCXZ"};

  CE_ERROR("HELLO." == all_caps(strs[0]), "Not equal!");
  CE_ERROR("123456789({[|]})`~QAZQAZWEBWEBJILLJILL<>,.:;/?!@#$%^&*" == all_caps(strs[1]), "Not equal!");
  CE_ERROR("QWERTYUIOPASDFGHJKLZXCVBNM" == all_caps(strs[2]), "Not equal!");
  CE_ERROR("POIUYTREWQLKJHGFDSAMNBVCXZ" == all_caps(strs[3]), "Not equal!");
  CE_ERROR(std::string{} == all_caps(""), "Not empty!");

  std::cout << "There should be 1 warning above. If not, something is wrong.\n";

  CE_FATAL(0, "This should abort the program!");
  puts("If you see this message, fatal error wasn't handled!");
  return 0;
}
