#include "stringbuilder.h"
#include <iostream>
char* remove_extra_spaces(char *destination, const char *source, int *res_size)
{
  StringBuilder stringBuilder;
  int j = 0;
  while (source[j] == ' ')
  {
    j++;
  }
  int i = 0;
  while (source[j])
  {
    if (source[j] == ' ')
    {
      while (source[j] == ' ')
      {
        j++;
      }
      stringBuilder.add_char(' ');
      j--;
    }
    else
    {
      stringBuilder.add_char(source[j]);
    }
    i++;
    j++;
  }
  int new_size = stringBuilder.get_size();
  while (stringBuilder.get_char(new_size - 1) == ' ')
  {
    stringBuilder.remove_char(new_size - 1);
    new_size--;
  }
  *res_size = stringBuilder.get_size();
  char *dop = stringBuilder.get_string();
  for (int k = 0; k < stringBuilder.get_size(); k++)
  {
    destination[k] = dop[k];
  }
  delete[] dop;
  return destination;
}
int main()
{
  int size = 5;
  char* str = {'d', ' ', ' ', ' ', 'a', ' '};
  char* res = new char[size];
  remove_extra_spaces(res, str, &size);
  std::cout << size;
  for (int i = 0; i < size; i++)
  {
    std::cout << res[i];
  }
  return 0;
}
