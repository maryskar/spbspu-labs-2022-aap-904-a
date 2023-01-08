#include "rectangle.h"
#include <stdexcept>

kryuchkova::Rectangle::Rectangle(const point_t &lb_point, const point_t &ru_point):
  lb_point_(lb_point),
  ru_point_(ru_point)
{
  if (lb_point.x >= ru_point.x || lb_point.y >= ru_point.y)
  {
    throw std::invalid_argument("It's not a rectangle");
  }
}

std::string kryuchkova::Rectangle::getName() const
{
  return "RECTANGLE";
}

double kryuchkova::Rectangle::getArea() const
{
  rectangle_t rect = getFrameRect();
  return rect.height * rect.width;
}

kryuchkova::rectangle_t kryuchkova::Rectangle::getFrameRect() const
{
  double width = ru_point_.x - lb_point_.x;
  double height = ru_point_.y - lb_point_.y;
  point_t pos = kryuchkova::getCentre(lb_point_, ru_point_);
  return rectangle_t{width, height, pos};
}

void kryuchkova::Rectangle::move(const double dx, const double dy)
{
  movePoint(lb_point_, point_t{dx, dy});
  movePoint(ru_point_, point_t{dx, dy});
}

void kryuchkova::Rectangle::move(const point_t point)
{
  point_t pos = kryuchkova::getCentre(lb_point_, ru_point_);
  double dx = point.x - pos.x;
  double dy = point.y - pos.y;
  move(dx, dy);
}

void kryuchkova::Rectangle::scale(const double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("scaling koef must be positive");
  }
  double width = ru_point_.x - lb_point_.x;
  double height = ru_point_.y - lb_point_.y;
  double dx = ((k - 1) * width) / 2;
  double dy = ((k - 1) * height) / 2;
  lb_point_.x -= dx;
  lb_point_.y -= dy;
  ru_point_.x += dx;
  ru_point_.y += dy;
}

kryuchkova::Shape *kryuchkova::Rectangle::clone() const
{
  return new Rectangle(lb_point_, ru_point_);
}

kryuchkova::point_t kryuchkova::getCentre(const kryuchkova::point_t point1, const kryuchkova::point_t point2)
{
  return point_t{(point1.x + point2.x) / 2, (point1.y + point2.y) / 2};
}
