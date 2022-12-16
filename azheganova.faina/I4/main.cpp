#include<iostream>
#include <fstream>
#include <cstddef>
#include <cstring>
#include"countrowswithdifferentelements.h"
#include"findstringwithconsecutiveequalelements.h"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "error";
    return 1;
  }
  size_t m = 0;
  size_t n = 0;
  std::ifstream inputfile(argv[2]);
  if (!inputfile.is_open())
  {
    std::cout << "file open error";
    return 1;
  }
  inputfile >> m;
  inputfile >> n;
  std::ofstream outputfile(argv[3]);
  if (!outputfile.is_open())
  {
    std::cout << "file open error";
    return 1;
  }
  if (!strcmp(argv[1], "1"))
  {
    int arr[1000];
    if (( m * n ) > 1000)
    {
      std::cout << "too much elements";
      return 1;
    }
    for (size_t i = 0; i < m; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        inputfile >> arr[m * i + j];
        if (!inputfile)
        {
          std::cout << "elements read error";
          return 1;
        }
      }
    }
    outputfile << countRowsWithDifferentElements(arr, m, n) << "\n";
    if (!outputfile)
    {
      std::cout << "number write error";
      return 1;
    }
  }
  else if (!strcmp(argv[1], "2"))
  {
    if (( m * n ) == 0)
    {
      outputfile << "0";
      return 0;
    }
    int* arr = new int[ m * n ];
    for (size_t i = 0; i < m; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        inputfile >> arr[i * m + j];
        if (!inputfile)
        {
          std::cout << "elements read error";
          delete[] arr;
          return 1;
        }
      }
    }
    outputfile << findStringWithConsecutiveEqualElements(arr, m, n) << "\n";
    if (!outputfile)
    {
      std::cout << "number write error";
      return 1;
    }
    delete[] arr;
  }
  else
  {
    std::cout << "errow";
    return 1;
  }
  return 0;
}
