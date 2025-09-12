#define _LIBCPP_REMOVE_TRANSITIVE_INCLUDES

#include "../src/custom_errors.h"
#include <string>

static_assert(sizeof(char) == 1, "God has left us!");

// src - reference of source string
static std::string malloc_all_caps(std::string const & src) {
  std::string res{};
  const std::string::size_type size = src.size();
  CE_WARNING(size != 0, "No size for the string!");
  if (size == 0) {
    return res;
  }

  try {
    res.reserve(size);
  } catch (...) {
    CE_WARNING(false, "Couldn't malloc new string!");
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

  CE_ERROR("HELLO." == malloc_all_caps(strs[0]), "Not equal!", CE_ERROR_TYPE_REGULAR);
  CE_ERROR("123456789({[|]})`~QAZQAZWEBWEBJILLJILL<>,.:;/?!@#$%^&*" == malloc_all_caps(strs[1]),
           "Not equal!",
           CE_ERROR_TYPE_REGULAR);
  CE_ERROR("QWERTYUIOPASDFGHJKLZXCVBNM" == malloc_all_caps(strs[2]), "Not equal!", CE_ERROR_TYPE_REGULAR);
  CE_ERROR("POIUYTREWQLKJHGFDSAMNBVCXZ" == malloc_all_caps(strs[3]), "Not equal!", CE_ERROR_TYPE_REGULAR);
  CE_ERROR(std::string{} == malloc_all_caps(""), "Not empty!", CE_ERROR_TYPE_REGULAR);

  std::cout << "There should be 1 warning above. If not, something is wrong.\n";

  CE_ERROR(0, "This should abort the program!", CE_ERROR_TYPE_FATAL);
  puts("If you see this message, fatal error wasn't handled!");
  return 0;
}
