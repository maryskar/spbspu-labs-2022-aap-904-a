#include <iostream>
#include <fstream>
#include <cstring>
#include "countarrays.h"
int main(int argc, char **argv)
{
  if (argc < 4 || argc > 4)
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 2;
  }
  char *taskNumber = argv[1];
  std::string fileIn = argv[2];
  std::string fileOut = argv[3];
  std::fstream fileInput(fileIn);
  std::ofstream fileOutput(fileOut);
  if (!fileInput.is_open())
  {
    std::cerr << "Error while opening file " << fileIn << ".\n";
    return 2;
  }
  if (!fileOutput.is_open())
  {
    std::cerr << "Error while opening file " << fileOut << ".\n";
    return 2;
  }
  size_t rows = 0;
  fileInput >> rows;
  if (!fileInput)
  {
    std::cerr << "Error while reading rows.\n";
    return 2;
  }
  size_t columns = 0;
  fileInput >> columns;
  if (!fileInput)
  {
    std::cerr << "Error while reading columns.\n";
    return 2;
  }
  if ((rows == 0) || (columns == 0))
  {
    std::cout << "Empty array.\n";
    return 0;
  }
  if (!strcmp(taskNumber, "1"))
  {
    size_t arraySize = rows * columns;
    int array[1000];
    if (arraySize > 1000)
    {
      std::cerr << "Maximum possible array size exceeded.\n";
      return 2;
    }
    for (size_t i = 0; i < arraySize; i++)
    {
      fileInput >> array[i];
      if (!fileInput)
      {
        std::cerr << "Error while reading file " << fileIn << "\n";
        return 2;
      }
    }
    size_t countDivEl = countDiverseElements(array, rows, columns);
    size_t countEqSum = countEqualSum(array, rows, columns);
    try
    {
      fileOutput << countDivEl << " " << countEqSum;
    }
    catch (...)
    {
      std::cerr << "Error while writing result.\n";
      return 2;
    }
  }
  if (!strcmp(taskNumber, "2"))
  {
    size_t matrixN = rows;
    size_t matrixSize = matrixN * matrixN;
    int * matrix = nullptr;
    try
    {
      matrix = new int[matrixN * matrixN];
    }
    catch (...)
    {
      std::cerr << "Error while creating matrix.\n";
      return 2;
    }
    for (size_t i = 0; i < matrixSize; i++)
    {
      fileInput >> matrix[i];
      if (!fileInput)
      {
        std::cerr << "Error while reading file " << fileIn << ".\n";
        delete[] matrix;
        return 2;
      }
    }
    try
    {
      smoothedMatrix = new int[matrixSize];
    }
    catch (...)
    {
      std::cerr << "Error while creating smoothed matrix.\n";
      return 2;
    }
    size_t countSuccEqEl = countSuccessionEqualElements(matrix, matrixN);
    smoothMatrix(matrix, smoothedMatrix, matrixN);
    size_t countUpMainDiag = countUpperMainDiagonal(smoothedMatrix, matrixN);
    delete[] smoothedMatrix;
    delete[] matrix;
    try
    {
      fileOutput << countSuccEqEl << " " << countUpMainDiag;
    }
    catch (...)
    {
      std::cerr << "Error while writing result.\n";
      delete[] smoothedMatrix;
      delete[] matrix;
      return 2;
    }
  }
}
