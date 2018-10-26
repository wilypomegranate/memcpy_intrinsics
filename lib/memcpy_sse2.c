#include "memcpy_sse2.h"


void* memcpy_sse2(void* dest, const void* src, size_t length) {

  /* If less that REG_SIZE, just do a regular memcpy. */
  if (length < REG_SIZE) {
    return memcpy(dest, src, length);
  }

  /* Calculate how much unaligned data is at the beginning. */

  uintptr_t src_address = (uintptr_t)src;

  size_t unaligned_length = REG_SIZE - (src_address % REG_SIZE);
  size_t aligned_length = 0;

  /* If the buffer is unaligned. */
  if (unaligned_length != REG_SIZE) {
    /* TODO Should use 4 and 8 byte aligned copies first. */
    memcpy(dest, src, unaligned_length);
    aligned_length = length - unaligned_length;
  }
  else {
    unaligned_length = 0;
  }

  /* Copy until the unaligned end. */
  size_t num_loops = aligned_length / REG_SIZE;

  char* aligned_src = (char*)src + unaligned_length;
  char* aligned_dest = (char*)dest + unaligned_length;

  for (size_t i = 0; i < num_loops; ++i) {
    __m128i* offset_src = (__m128i*)(aligned_src + (REG_SIZE * i));
    __m128i src_reg = _mm_load_si128(offset_src);
    __m128i* offset_dst = (__m128i*)(aligned_dest + (REG_SIZE * i));
    _mm_store_si128(offset_dst, src_reg);
  }

  /* Handle unaligned end. */
  char* current_src_offset = aligned_src + (REG_SIZE * num_loops);
  char* current_dest_offset = aligned_dest + (REG_SIZE * num_loops);
  size_t remainder = aligned_length - (REG_SIZE * num_loops);
  memcpy(current_dest_offset, current_src_offset, remainder);

  return dest;
}
