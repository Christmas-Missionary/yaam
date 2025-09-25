#include "../src/custom_errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static_assert(sizeof(char) == 1, "God has left us!");

// src - source string to convert, size - length of string + null byte
// Example: ("Cats", 5) -> "CATS"
static char * malloc_all_caps(const char * src, const size_t size) {
  CE_WARN(src != NULL, "No string at all to convert!");
  CE_WARN(size != 0, "No size for the string!");
  if (src == NULL || size == 0) {
    return NULL;
  }
  CE_WARN(src[0] != 0, "No size for the string!");
  if (src[0] == 0) {
    return NULL;
  }

  char * res = malloc(size);
  CE_WARN(res != NULL, "Couldn't malloc new string!");
  if (res == NULL) {
    return NULL;
  }

  size_t index = 0;
  for (; (index < size - 1) && (src[index] != 0); index++) {
    const char chr = src[index];
    if (chr >= 'a' && chr <= 'z') {
      res[index] = (char)(chr - 32);
      continue;
    }
    res[index] = chr;
  }
  CE_FATAL(index <= size, "Index is greater than length of string!");
  CE_WARN(index == size - 1, "String is less than length given!");
  res[index] = 0;
  return res;
}

typedef struct {
  char * data;
  size_t size;
} fat_str;

int main(void) {
#ifdef __STDC_VERSION__
  printf("C standard version: %ld\n", __STDC_VERSION__);
#endif
  fat_str strs[4] = {(fat_str){"Hello.", 7}, (fat_str){"123456789({[|]})`~QAZqazwebWEBJILLjill<>,.:;/?!@#$%^&*", 55},
                     (fat_str){"qwertyuiopasdfghjklzxcvbnm", 27}, (fat_str){"POIUYTREWQLKJHGFDSAMNBVCXZ", 27}};

  CE_ERROR(strcmp("HELLO.", malloc_all_caps(strs[0].data, strs[0].size)) == 0, "Not equal!");
  CE_ERROR(
    strcmp("123456789({[|]})`~QAZQAZWEBWEBJILLJILL<>,.:;/?!@#$%^&*", malloc_all_caps(strs[1].data, strs[1].size)) == 0,
    "Not equal!");
  CE_ERROR(strcmp("QWERTYUIOPASDFGHJKLZXCVBNM", malloc_all_caps(strs[2].data, strs[2].size)) == 0, "Not equal!");
  CE_ERROR(strcmp("POIUYTREWQLKJHGFDSAMNBVCXZ", malloc_all_caps(strs[3].data, strs[3].size)) == 0, "Not equal!");
  CE_ERROR(strcmp("TEST", malloc_all_caps("Testing", 5)) == 0, "Not equal!");
  CE_ERROR(malloc_all_caps(NULL, 1) == NULL, "Not null!");
  CE_ERROR(malloc_all_caps("A", 0) == NULL, "Not null!");
  CE_ERROR(malloc_all_caps("", 1) == NULL, "Not null!");
  puts("There should be 3 warnings above. If not, something is wrong.");
  CE_ERROR(0, "This should abort the program!");
  puts("If you see this message, assertion wasn't handled!");
  return 0;
}
