﻿#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstring>
#include "count_rows_without_zero.h"
#include "count_diagonals_parallel_to_secondary_without_zero.h"

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "ERROR: the number of arguments does not match the required\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "ERROR: file cannot be opened\n";
    return 1;
  }
  size_t rows = 0;
  size_t columns = 0;
  input >> rows >> columns;
  if (!input)
  {
    std::cerr << "ERROR: file cannot be read\n";
    return 1;
  }

  if (rows * columns > 1000)
  {
    std::cerr << "ERROR: matrix is too large\n";
    return 1;
  }
  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "ERROR: file cannot be read\n";
    return 1;
  }

  if (!std::strcmp(argv[1], "1"))
  {
    int matrix[1000];
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < columns; j++)
      {
        input >> matrix[rows * i + j];
        if (!input)
        {
          std::cerr << "ERROR: file cannot be read\n";
          return 1;
        }
      }
    }
    output << countRowsWithoutZero(matrix, rows, columns) << '\n';
    if (!output)
    {
      std::cerr << "ERROR: file cannot be read\n";
      return 1;
    }
  }
  else if (!std::strcmp(argv[1], "2"))
  {
    int* dynamicMatrix = nullptr;
    try
    {
      dynamicMatrix = new int[rows * columns];
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        delete[] dynamicMatrix;
        return 1;
    }
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < columns; j++)
      {
        input >> dynamicMatrix[rows * i + j];
        if (!input)
        {
          std::cerr << "ERROR: file cannot be read\n";
          delete[] dynamicMatrix;
          return 1;
        }
      }
    }

    size_t squareMatrixSize = std::min(rows, columns);

    int* squareMatrix = nullptr;
    if (rows == columns)
    {
      squareMatrix = dynamicMatrix;
      dynamicMatrix = nullptr;
    }
    else
    {
      try
      {
        squareMatrix = new int[squareMatrixSize * squareMatrixSize];
      }
      catch (std::exception& e)
      {
        std::cerr << e.what() << '\n';
        delete[] dynamicMatrix;
        delete[] squareMatrix;
        return 1;
      }
      if (columns < rows)
      {
        for (size_t i = 0; i < (squareMatrixSize * squareMatrixSize); ++i)
        {
          squareMatrix[i] = dynamicMatrix[i];
        }
      }
      else if (columns > rows)
      {
        for (size_t i = 0; i < squareMatrixSize; ++i)
        {
          for (size_t j = 0; j < squareMatrixSize; ++j)
          {
            squareMatrix[squareMatrixSize * i + j] = dynamicMatrix[columns * i + j];
          }
        }
      }
    }
    if (squareMatrixSize == 0)
    {
      std::cout << "Empty matrix\n";
      return 0;
      delete[] dynamicMatrix;
      delete[] squareMatrix;
    }
    output << countDiagonalsParallelToSecondaryWithoutZero(squareMatrix, squareMatrixSize) << '\n';
    if (!output)
    {
      std::cerr << "ERROR: file cannot be read\n";
      return 1;
    }

    delete[] dynamicMatrix;
    delete[] squareMatrix;
  }
  else
  {
    std::cerr << "ERROR: invalid argument\n";
    return 1;
  }
  return 0;
}
