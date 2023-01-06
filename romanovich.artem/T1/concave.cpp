#include "concave.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <array>
#include <iostream>
Concave::Concave(const point_t &A, const point_t &B, const point_t &C, const point_t &D):
  a_(A),
  b_(B),
  c_(C),
  d_(D)
{
  if (!goodConcaveInput())
  {
    throw std::invalid_argument("Bad concave input.");
  }
}
bool Concave::goodConcaveInput() const
{
  return pointInsideTriangle(triangle_t{a_, b_, c_}, d_)
         && isTriangle(splitIntoTriangles());
}
std::array< double, 6 > Concave::splitIntoTriangles() const
{
  double a = twoPointsDistance(a_, c_);
  double b = twoPointsDistance(c_, b_);
  double c = twoPointsDistance(a_, b_);
  double a1 = twoPointsDistance(c_, d_);
  double b1 = b;
  double c1 = twoPointsDistance(d_, b_);
  std::array< double, 6 > arr = {a, b, c, a1, b1, c1};
  return arr;
}
double Concave::getArea() const
{
  std::array< double, 6 > sides = splitIntoTriangles();
  double a = sides[0];
  double b = sides[1];
  double c = sides[2];
  double a1 = sides[3];
  double b1 = sides[4];
  double c1 = sides[5];
  double p = (a + b + c) / 2;
  double p1 = (a1 + b1 + c1) / 2;
  double s = std::sqrt(p * (p - a) * (p - b) * (p - c));
  double s1 = std::sqrt(p1 * (p1 - a1) * (p1 - b1) * (p1 - c1));
  return s - s1;
}
rectangle_t Concave::getFrameRect() const
{
  double sup = std::max({a_.y, b_.y, c_.y});
  double inf = std::min({a_.y, b_.y, c_.y});
  double left = std::min({a_.x, b_.x, c_.x});
  double right = std::max({a_.x, b_.x, c_.x});
  return {(right + left) / 2, (sup + inf) / 2, right - left, sup - inf};
}
void Concave::move(double dx, double dy)
{
  point_t *points[4]{&a_, &b_, &c_, &d_};
  for (point_t *p: points)
  {
    addVectorToPoint(p, dx, dy);
  }
}
void Concave::move(const point_t &position)
{
  point_t s = shift(position, getFrameRect().pos);
  move(s.x, s.y);
}
void Concave::scale(double k)
{
  point_t center{getFrameRect().pos.x, getFrameRect().pos.y};
  point_t *point[4]{&a_, &b_, &c_, &d_};
  for (point_t *p: point)
  {
    multiplyVector(center, p, k);
  }
}
Shape *Concave::clone() const
{
  return new Concave(a_, b_, c_, d_);
}
