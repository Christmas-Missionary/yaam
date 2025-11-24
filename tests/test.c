// Copyright (c) 2025 Christmas_Missionary - BSD Zero Clause License

#include "../src/custom_errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static_assert(sizeof(char) == 1, "God has left us!");

#define MAX_ITER 1000

// src - destination buffer, source string to convert, size -> ptr to destination buffer or NULL if failed
// Example: ("Cats", 5) -> "CATS"
static char * all_caps(char * restrict dst, const char * src, const size_t size) {
  CE_WARN(dst != NULL, "No string at all to return!");
  CE_WARN(src != NULL, "No string at all to convert!");
  CE_WARN(size != 0, "No size for the string!");
  CE_WARN(size <= 1000, "All loops should be at most 1000 iterations!");
  if (src == NULL || dst == NULL || size == 0) {
    return NULL;
  }
  CE_WARN(src[0] != 0, "No size for the string!");
  if (src[0] == 0) {
    return NULL;
  }

  size_t index = 0;
  for (; (index < size - 1) && (src[index] != 0); index++) {
    const char chr = src[index];
    if (chr >= 'a' && chr <= 'z') {
      dst[index] = (char)(chr - 32);
      continue;
    }
    dst[index] = chr;
  }
  CE_ERROR(index <= size, "Index is greater than length of string!");
  CE_WARN(index == size - 1, "String is less than length given!");
  dst[index] = 0;
  return dst;
}

typedef struct {
  char * data;
  size_t size;
} fat_str;

int main(void) {
#ifdef _WIN32
  if (set_windows_colors() != 0) {
    printf("Colored text output will not work on windows!\n");
  }
#endif
#ifdef __STDC_VERSION__
  printf("C standard version: %ld\n", __STDC_VERSION__);
#endif
  fat_str strs[4] = {(fat_str){"Hello.", 7}, (fat_str){"123456789({[|]})`~QAZqazwebWEBJILLjill<>,.:;/?!@#$%^&*", 55},
                     (fat_str){"qwertyuiopasdfghjklzxcvbnm", 27}, (fat_str){"POIUYTREWQLKJHGFDSAMNBVCXZ", 27}};

  char buf[60];

  CE_ERROR(strcmp("HELLO.", all_caps(buf, strs[0].data, strs[0].size)) == 0, "Not equal!");
  CE_ERROR(
    strcmp("123456789({[|]})`~QAZQAZWEBWEBJILLJILL<>,.:;/?!@#$%^&*", all_caps(buf, strs[1].data, strs[1].size)) == 0,
    "Not equal!");
  CE_ERROR(strcmp("QWERTYUIOPASDFGHJKLZXCVBNM", all_caps(buf, strs[2].data, strs[2].size)) == 0, "Not equal!");
  CE_ERROR(strcmp("POIUYTREWQLKJHGFDSAMNBVCXZ", all_caps(buf, strs[3].data, strs[3].size)) == 0, "Not equal!");
  CE_ERROR(strcmp("TEST", all_caps(buf, "Testing", 5)) == 0, "Not equal!");
  CE_FATAL(all_caps(buf, NULL, 1) == NULL, "Not null!");
  CE_ERROR(all_caps(buf, "A", 0) == NULL, "Not null!");
  CE_ERROR(all_caps(buf, "", 1) == NULL, "Not null!");
  CE_ERROR(all_caps(NULL, "f", 1) == NULL, "Not null!");
  puts("There should be 4 warnings above. If not, something is wrong.");
  CE_ERROR(0, "This should abort the program!");
  puts("If you see this message, assertion wasn't handled!");
  return 0;
}
