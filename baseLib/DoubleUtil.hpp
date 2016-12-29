#include <stdio.h>
#include <unistd.h>
#include <iostream>

float floatPrecision(float f)
{
  union {unsigned int int_val; float flt_val;} union_hack;
  union_hack.flt_val = f;
  union_hack.int_val = (((union_hack.int_val & 0x7f800000) >> 23 ) - 23 ) << 23;
  return union_hack.flt_val;
}

float floatEpsilon(float f)
{
  union {unsigned int int_val; float flt_val;} union_hack;
  union_hack.flt_val = f;
  union_hack.int_val = (((union_hack.int_val & 0x7f800000) >> 23 ) - 22 ) << 23;
  return union_hack.flt_val;
}

static inline bool femore(float d1, float d2)
{
  return d1 >= d2 - floatEpsilon(std::min(d1, d2));
}
