#include "compositeshape.h"
#include <algorithm>
CompositeShape::CompositeShape(Shape **shapes, size_t size):
  shapes_(nullptr),
  size_(size)
{
  shapes_ = new Shape*[size_];
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] = shapes[i]->clone();
  }
}
double CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}
rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t rectangle = shapes_[0]->getFrameRect();
  double x_min = rectangle.getLeftDownPoint().x;
  double y_min = rectangle.getLeftDownPoint().y;
  double x_max = rectangle.getRightUpPoint().x;
  double y_max = rectangle.getRightUpPoint().y;
  for (size_t i = 0; i < size_; i++)
  {
    rectangle = shapes_[i]->getFrameRect();
    x_min = std::min(x_min, rectangle.getLeftDownPoint().x);
    y_min = std::min(y_min, rectangle.getLeftDownPoint().y);
    x_max = std::max(x_max, rectangle.getRightUpPoint().x);
    y_max = std::max(y_max, rectangle.getRightUpPoint().y);
  }
  return rectangle_t(x_min, y_min, x_max, y_max);
}
point_t CompositeShape::getCenterOfGravity() const
{
  double x_sum = 0.0;
  double y_sum = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    point_t
  }
}
