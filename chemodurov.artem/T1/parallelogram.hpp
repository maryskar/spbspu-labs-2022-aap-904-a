#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP
#include "polygon.hpp"

namespace chemodurov
{
  class Parallelogram: public chemodurov::Shape
  {
   public:
    Parallelogram(const chemodurov::point_t & fst, const point_t & sec, const point_t & trd);
    ~Parallelogram();
    double getArea() const;
    chemodurov::rectangle_t getFrameRect() const;
    void move(const chemodurov::point_t & pos);
    void move(double dx, double dy);
    void scale(double k);
    chemodurov::Shape * clone() const;
   private:
    chemodurov::Polygon p;
  };
}

#endif
