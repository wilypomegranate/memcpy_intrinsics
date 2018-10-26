cmake_minimum_required(VERSION 3.7)

project(memcpy_intrinsics C)

set(CMAKE_C_FLAGS "-std=c99 -msse -msse2 -mavx -mavx2 -Werror -Wall -pedantic -Wextra")

include_directories(include)

add_library(
  memcpy_sse2
  lib/memcpy_sse2.c
  )
