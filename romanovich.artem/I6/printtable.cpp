#include "printtable.h"
#include "comparedoubles.h"
#include <iomanip>
#include <cmath>
#include <cstddef>
#include <ostream>
void printTableRow(std::ostream & out, double x, double absError, size_t numberMax)
{
  out << std::setw(5) << x << " ";
  out << std::setw(10) << std::setprecision(5) << mySinh(x, absError, numberMax) << " ";
  out << std::setw(10) << std::setprecision(5) << sinh(x) << "\n";
}
void printTable(std::ostream & out, double left, double right, double step, double x, double absError, size_t numberMax)
{
  if (left > right)
  {
    double tmp = left;
    left = right;
    right = tmp;
  }
  for (double value=left; value <= right; value += step)
  {
    if (isSmaller(std::abs(value), step/10, 1e-6))
    {
      value = 0;
    }
    printTableRow(out, value, absError, numberMax);
  }
}
