#include "../src/custom_errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static_assert(sizeof(char) == 1, "God has left us!");

// src - source string to convert, size - length of string + null byte
// Example: ("Cats", 5) -> "CATS"
static char * malloc_all_caps(const char * src, const size_t size) {
  CE_ERROR(src != NULL, CE_ERROR_TYPE_WARNING, "No string at all to convert!");
  CE_ERROR(size != 0, CE_ERROR_TYPE_WARNING, "No size for the string!");
  if (src == NULL || size == 0) {
    return NULL;
  }
  CE_ERROR(src[0] != 0, CE_ERROR_TYPE_WARNING, "No size for the string!");
  if (src[0] == 0) {
    return NULL;
  }

  char * res = malloc(size);
  CE_ERROR(res != NULL, CE_ERROR_TYPE_WARNING, "Couldn't malloc new string!");
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
  CE_ERROR(index <= size, CE_ERROR_TYPE_FATAL, "Index is greater than length of string!");
  CE_ERROR(index == size - 1, CE_ERROR_TYPE_WARNING, "String is less than length given!");
  res[index] = 0;
  return res;
}

typedef struct {
  char * data;
  size_t size;
} fat_str;

int main(void) {
  fat_str strs[4] = {(fat_str){"Hello.", 7}, (fat_str){"123456789({[|]})`~QAZqazwebWEBJILLjill<>,.:;/?!@#$%^&*", 55},
                     (fat_str){"qwertyuiopasdfghjklzxcvbnm", 27}, (fat_str){"POIUYTREWQLKJHGFDSAMNBVCXZ", 27}};

  CE_ERROR(strcmp("HELLO.", malloc_all_caps(strs[0].data, strs[0].size)) == 0, CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR(
    strcmp("123456789({[|]})`~QAZQAZWEBWEBJILLJILL<>,.:;/?!@#$%^&*", malloc_all_caps(strs[1].data, strs[1].size)) == 0,
    CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR(strcmp("QWERTYUIOPASDFGHJKLZXCVBNM", malloc_all_caps(strs[2].data, strs[2].size)) == 0,
           CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR(strcmp("POIUYTREWQLKJHGFDSAMNBVCXZ", malloc_all_caps(strs[3].data, strs[3].size)) == 0,
           CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR(strcmp("TEST", malloc_all_caps("Testing", 5)) == 0, CE_ERROR_TYPE_ASSERTION, "Not equal!");
  CE_ERROR(malloc_all_caps(NULL, 1) == NULL, CE_ERROR_TYPE_ASSERTION, "Not null!");
  CE_ERROR(malloc_all_caps("A", 0) == NULL, CE_ERROR_TYPE_ASSERTION, "Not null!");
  CE_ERROR(malloc_all_caps("", 1) == NULL, CE_ERROR_TYPE_ASSERTION, "Not null!");
  puts("There should be 3 warnings above. If not, something is wrong.");
  return 0;
}
