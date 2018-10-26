#include <string.h>
#include <stdint.h>
#include <emmintrin.h>

#define REG_SIZE 16

void* memcpy_sse2(void* dest, const void* src, size_t length);
