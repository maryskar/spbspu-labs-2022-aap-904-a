#include "compositeshape.hpp"
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include "shape.hpp"
#include "base-types.hpp"

odintsov::CompositeShape::CompositeShape():
  CompositeShape(5)
{}

odintsov::CompositeShape::CompositeShape(size_t cap):
  size_(0),
  cap_(cap),
  shapes(new Shape*[cap_])
{}

odintsov::CompositeShape::CompositeShape(const odintsov::CompositeShape& shp):
  CompositeShape(shp.cap_)
{
  try {
    for (size_t i = 0; i < shp.size(); i++) {
      Shape* clone = shp[i]->clone();
      push_back(clone);
    }
  } catch (...) {
    while (!empty()) {
      pop_back();
    }
    delete [] shapes;
    throw;
  }
}


odintsov::CompositeShape::CompositeShape(odintsov::CompositeShape&& shp):
  size_(shp.size()),
  cap_(shp.cap_),
  shapes(shp.shapes)
{
  shp.shapes = nullptr;
  shp.cap_ = 0;
  shp.size_ = 0;
}

odintsov::CompositeShape::~CompositeShape()
{
  while (!empty()) {
    pop_back();
  }
  delete [] shapes;
}

odintsov::CompositeShape& odintsov::CompositeShape::operator=(const odintsov::CompositeShape& shp)
{
  Shape** clonedShapes = new Shape*[shp.cap_];
  for (size_t i = 0; i < shp.size(); i++) {
    try {
      clonedShapes[i] = shp[i]->clone();
    } catch (...) {
      for (size_t j = 0; j < i; i++) {
        delete clonedShapes[j];
      }
      delete [] clonedShapes;
      throw;
    }
  }
  while(!empty()) {
    pop_back();
  }
  delete [] shapes;
  shapes = clonedShapes;
  cap_ = shp.cap_;
  size_ = shp.size_;
  return *this;
}

odintsov::CompositeShape& odintsov::CompositeShape::operator=(odintsov::CompositeShape&& shp)
{
  while(!empty()) {
    pop_back();
  }
  size_ = shp.size_;
  cap_ = shp.cap_;
  shapes = shp.shapes;
  shp.size_ = 0;
  shp.cap_ = 0;
  shp.shapes = nullptr;
  return *this;
}

double odintsov::CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size(); i++) {
    area += shapes[i]->getArea();
  }
  return area;
}

odintsov::rectangle_t odintsov::CompositeShape::getFrameRect() const
{
  if (empty()) {
    throw std::logic_error("no shapes inside CompositeShape");
  }
  rectangle_t rect = shapes[0]->getFrameRect();
  double leftX = rect.pos.x - rect.width * 0.5;
  double rightX = rect.pos.x + rect.width * 0.5;
  double bottomY = rect.pos.y - rect.height * 0.5;
  double topY = rect.pos.y + rect.height * 0.5;
  for (size_t i = 1; i < size(); i++) {
    rect = shapes[i]->getFrameRect();
    leftX = std::min(leftX, rect.pos.x - rect.width * 0.5);
    rightX = std::max(rightX, rect.pos.x + rect.width * 0.5);
    bottomY = std::min(bottomY, rect.pos.y - rect.height * 0.5);
    topY = std::max(topY, rect.pos.y + rect.height * 0.5);
  }
  return rectangle_t{rightX - leftX, topY - bottomY, {(leftX + rightX) * 0.5, (bottomY + topY) * 0.5}};
}

void odintsov::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size(); i++) {
    shapes[i]->move(dx, dy);
  }
}

void odintsov::CompositeShape::move(const point_t& pos)
{
  point_t middle = getMiddlePoint();
  move(pos.x - middle.x, pos.y - middle.y);
}

void odintsov::CompositeShape::scale(double k)
{
  point_t middle = getMiddlePoint();
  for (size_t i = 0; i < size(); i++) {
    isoScale(shapes[i], middle, k);
  }
}

odintsov::point_t odintsov::CompositeShape::getMiddlePoint() const
{
  return getFrameRect().pos;
}

void odintsov::CompositeShape::push_back(Shape* shp)
{
  if (size() == cap_) {
    extend(cap_ + 10);
  }
  shapes[size_++] = shp;
}

void odintsov::CompositeShape::pop_back()
{
  if (size_ == 0) {
    return;
  }
  delete shapes[--size_];
  shapes[size_] = nullptr;
}

odintsov::Shape* odintsov::CompositeShape::at(size_t id) const
{
  if (id >= size())
  {
    throw std::out_of_range("index out of range");
  }
  return shapes[id];
}

odintsov::Shape* odintsov::CompositeShape::operator[](size_t id) const
{
  return shapes[id];
}

bool odintsov::CompositeShape::empty() const
{
  return size() == 0;
}

size_t odintsov::CompositeShape::size() const
{
  return size_;
}

void odintsov::CompositeShape::extend(size_t newCap)
{
  if (newCap < cap_) {
    throw std::logic_error("attempt to shrink Shape container");
  }
  Shape** newShapes = new Shape*[newCap];
  for (size_t i = 0; i < size(); i++) {
    newShapes[i] = shapes[i];
  }
  delete [] shapes;
  shapes = newShapes;
  cap_ = newCap;
}

std::ostream& odintsov::outputCompositeShape(std::ostream& out, CompositeShape& composite)
{
  out << composite.getArea();
  for (size_t i = 0; i < composite.size(); i++) {
    rectangle_t rect = composite[i]->getFrameRect();
    out << ' ' << rect.pos.x - rect.width * 0.5 << ' ' << rect.pos.y - rect.height * 0.5;
    out << ' ' << rect.pos.x + rect.width * 0.5 << ' ' << rect.pos.y + rect.height * 0.5;
  }
  return out;
}
