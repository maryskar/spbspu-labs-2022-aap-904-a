#include "printtable.h"
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include "sqrt1minusxsquare.h"

void printRowInTable(std::ostream & out, double x, size_t max_members, double error)
{
  Sqrt1MinusXSquare sqrt1{0, 0};
  double sqrt_in_x = 0.0;
  try
  {
    sqrt_in_x = sqrt1(x, max_members, error);
  }
  catch (const std::runtime_error & e)
  {
    throw;
  }
  out << std::setw(5) << x << ' ';
  out << std::setw(10) << std::setprecision(5) << sqrt_in_x << ' ';
  out << std::setw(10) << std::setprecision(5) << 1 / (std::sqrt(1 - x * x));
}

void chemodurov::printTable(std::ostream & out, double left, double right, double step, size_t max_mem, double err)
{
  for (double i = left; i < right; i += step)
  {
    if (i > left && i < right)
    {
      try
      {
        printRowInTable(out << "\n", i, max_mem, err);
      }
      catch (const std::runtime_error & e)
      {
        throw;
      }
    }
    else
    {
      throw std::out_of_range("X is out of range");
    }
  }
}
