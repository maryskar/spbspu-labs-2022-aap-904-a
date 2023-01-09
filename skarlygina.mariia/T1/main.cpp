#include <iostream>
#include "shape.h"
#include "rectangle.h"
#include "ring.h"
#include "ellipse.h"
#include "make_output.h"
#include "figure_array.h"
#include "isotropic_scale.h"

int main()
{
  std::string figure = "";
  size_t size = 0;
  point_t point{};
  double coefficient = 0;
  bool isScale = false;
  bool isCommand = true;
  Shape** array_figures = new Shape*[size];
  do
  {
    std::cin >> figure;
    if (figure == "RECTANGLE")
    {
      Shape* rectangle = nullptr;
      try
      {
        double parameters[4]{};
        std::cin >> parameters[0] >> parameters[1] >> parameters[2] >> parameters[3];
        rectangle = new Rectangle({parameters[0], parameters[1]}, {parameters[2], parameters[3]});
        Shape** extend_array = FigureArray::extendArray(array_figures, rectangle, size);
        delete[] array_figures;
        array_figures = extend_array;
        size++;
      }
      catch (const std::invalid_argument& e)
      {
        std::cerr << e.what() << "\n";
        FigureArray::deleteArgument(rectangle, isCommand);
        continue;
      }
      catch (...)
      {
        makeErrorOutput("Error: could not read rectangle\n", size, array_figures);
        return 2;
      }
    }

    if (figure == "RING")
    {
      Shape* ring = nullptr;
      try
      {
        double parameters[4]{};
        std::cin >> parameters[0] >> parameters[1] >> parameters[2] >> parameters[3];
        ring = new Ring({parameters[0], parameters[1]}, parameters[3], parameters[2]);
        Shape** extend_array = FigureArray::extendArray(array_figures, ring, size);
        delete[] array_figures;
        size++;
      }
      catch (const std::invalid_argument& e)
      {
        std::cerr << e.what() << "\n";
        FigureArray::deleteArgument(ring, isCommand);
        continue;
      }
      catch (...)
      {
        makeErrorOutput("Error: could not read ring\n", size, array_figures);
        return 2;
      }
    }

    if (figure == "ELLIPSE")
    {
      Shape* ellipse = nullptr;
      try
      {
        double parameters[4]{};
        std::cin >> parameters[0] >> parameters[1] >> parameters[2] >> parameters[3];
        ellipse = new Ellipse({parameters[0], parameters[1]}, parameters[2], parameters[3]);
        Shape** extend_array = FigureArray::extendArray(array_figures, ellipse, size);
        delete[] array_figures;
        size++;
      }
      catch (const std::invalid_argument& e)
      {
        std::cerr << e.what() << "\n";
        FigureArray::deleteArgument(ellipse, isCommand);
        continue;
      }
      catch (...)
      {
        makeErrorOutput("Error: could not read ellipse\n", size, array_figures);
        return 2;
      }
    }

    if (figure == "SCALE")
    {
      isScale = true;
      try
      {
        std::cin >> point.x >> point.y >> coefficient;
        if (coefficient <= 0)
        {
          std::cerr << "Error: coefficient could not be under zero\n";
          FigureArray::deleteArray(size, array_figures);
          return 2;
        }
      }
      catch (...)
      {
        makeErrorOutput("Error: wrong parameters of the point, coefficient\n", size, array_figures);
        return 2;
      }
      break;
    }
  }
  while (std::cin);

  if (size > 0 && isScale)
  {
    makeOutput(std::cout, array_figures, size);
    for (size_t i = 0; i < size; i++)
    {
      makeIsotropicScaling(array_figures[i], point, coefficient);
    }
    makeOutput(std::cout, array_figures, size);
    if (!isCommand)
    {
      std::cerr << "Some figures are not correct\n";
    }
  }
  else if (!isScale)
  {
    FigureArray::deleteArray(size, array_figures);
    std::cerr << "Error: the final figure could be SCALE and size bigger than zero";
    return 2;
  }
  else if (size < 1)
  {
    FigureArray::deleteArray(size, array_figures);
    std::cerr << "Error: the final figure could be SCALE and size bigger than zero";
    return 2;
  }
  FigureArray::deleteArray(size, array_figures);
  return 0;
}
