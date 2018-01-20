/* Generic Helper/Utility functions */

#include <types.h>

// Contribution by ST Community member - gazor
uint8_t* appendStringChar(uint8_t* dest, const char* str)
{
  // Write string, preceeded by length byte, no termination character
  size_t len = 0;
  for(;;)
  {
    uint8_t c = (uint8_t) str[len];
    if(c == 0) break;
    dest[1+len] = c;
    len++;
  }
  dest[0] = (uint8_t) len;
  return dest + 1 + len;
}