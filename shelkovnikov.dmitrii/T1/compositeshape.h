#ifndef SPBSPU_LABS_2022_AAP_904_A_COMPOSITE_SHAPE_H
#define SPBSPU_LABS_2022_AAP_904_A_COMPOSITE_SHAPE_H
#include <cstddef>
#include <sstream>
#include "base_types.h"
#include "shape.h"
#include "rectangle.h"
#include "regular.h"
#include "polygon.h"
namespace dimkashelk
{
  class CompositeShape
  {
  public:
    CompositeShape();
    Shape* operator[](size_t id);
    const Shape* operator[](size_t id) const;
    ~CompositeShape();
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(point_t point);
    void move(double delta_x, double delta_y);
    void scale(double k);
    void push_back(Shape *shp);
    void push_back (Shape const *shp);
    void pop_back();
    Shape* at(size_t id);
    const Shape* at(size_t id) const;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void isotropicScaling(point_t point, double k);
  private:
    size_t size_;
    size_t capacity_;
    Shape **shapes_;
    CompositeShape(const CompositeShape &compositeShape);
    CompositeShape(CompositeShape &&compositeShape);
    CompositeShape& operator=(const CompositeShape &other);
    CompositeShape& operator=(CompositeShape &&tmp);
    void free();
  };
}
#endif
