#include "cstring_capacity_prev.h"
#include <cstring>
char* makeNewCapacityCString(char* cstring, size_t& capacity)
{
  char* newstring = new char[capacity + 20];
  strcpy (newstring, cstring);
  cstring = newstring;
  capacity += 20;
  cstring[capacity - 1] = '\0';
  return cstring;
}
