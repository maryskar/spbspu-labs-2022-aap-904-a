#include "printarray.hpp"

void print_array(int* arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    std::cout << arr[i] << " ";
  }
}
