#include "arrays.h"
#include <cstddef>
#include <cstring>
#include <stdexcept>

void fillArray(int* arr, size_t rows, size_t cols, std::ifstream& in)
{
  size_t size = rows * cols;
  for (size_t i = 0; i < size; ++i)
  {
    in >> arr[i];
    if (in.fail())
    {
      throw std::runtime_error("Error while readaing from file");
    }
  }
}

void printArray(std::ostream& out, const int* arr, size_t rows, size_t cols)
{
  for (size_t row = 0; row < rows; row++)
  {
    for (size_t col = 0; col < cols; col++)
    {
      out << arr[row * cols + col];
      if (col == (cols - 1) && row < (rows - 1))
      {
        out << "\n";
      }
      else
      {
        out << " ";
      }
    }
  }
}

size_t getPositiveRowsCount(const int* arr, size_t rows, size_t cols)
{
  size_t count = 0;
  for (size_t row = 0; row < rows; row++)
  {
    bool foundNegative = false;
    for (size_t col = 0; col < cols; col++)
    {
      if (arr[row * cols + col] < 0)
      {
        foundNegative = true;
        break;
      }
    }
    if (!foundNegative)
    {
      count++;
    }
  }
  return count;
}

int getMaxSumDiag(const int* arr, size_t size)
{
  size_t rows = size;
  size_t cols = size;
  int* sums = new int[2 * rows - 1] { 0 };
  for (size_t row = 0; row < rows; row++)
  {
    for (size_t col = 0; col < cols; col++)
    {
      size_t diagNum = row + col;
      sums[diagNum] += arr[row * cols + rows - 1 - col];
    }
  }
  size_t maxDiag = 0;
  for (size_t i = 1; i < rows * 2 - 1; i++)
  {
    if (i + 1 != rows && sums[i] > sums[maxDiag])
    {
      maxDiag = i;
    }
  }
  int maxSum = sums[maxDiag];
  delete[] sums;
  return maxSum;
}
