#define _LIBCPP_REMOVE_TRANSITIVE_INCLUDES

#include "../src/custom_errors.h"
#include <string>

static_assert(sizeof(char) == 1, "God has left us!");

// src - reference of source string
static std::string malloc_all_caps(std::string const& src) {
  std::string res {};
  const std::string::size_type size = src.size();
  CE_ERROR(size != 0, CE_ERROR_TYPE_WARNING, "No size for the string!");
  if (size == 0) {
    return res;
  }

  try {
    res.reserve(size);
  } catch (...){
    CE_ERROR(false, CE_ERROR_TYPE_WARNING, "Couldn't malloc new string!");
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

  const std::array<std::string, 4> strs = {"Hello.", "123456789({[|]})`~QAZqazwebWEBJILLjill<>,.:;/?!@#$%^&*", "qwertyuiopasdfghjklzxcvbnm", "POIUYTREWQLKJHGFDSAMNBVCXZ"};

  CE_ERROR("HELLO." == malloc_all_caps(strs[0]), CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR("123456789({[|]})`~QAZQAZWEBWEBJILLJILL<>,.:;/?!@#$%^&*" == malloc_all_caps(strs[1]), CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR("QWERTYUIOPASDFGHJKLZXCVBNM" == malloc_all_caps(strs[2]), CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR("POIUYTREWQLKJHGFDSAMNBVCXZ" == malloc_all_caps(strs[3]), CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR(std::string{} == malloc_all_caps(""), CE_ERROR_TYPE_ASSERTION, "Not empty!");

  std::cout << "There should be 1 warning above. If not, something is wrong.\n";

  CE_ERROR(0, CE_ERROR_TYPE_FATAL, "This should abort the program!");
  puts("If you see this message, fatal error wasn't handled!");
  return 0;
}
