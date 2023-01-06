#ifndef PROCESSINPUT_HPP
#define PROCESSINPUT_CPP

#include <iosfwd>
#include "compositeshape.hpp"

namespace odintsov {
  std::istream& processCommand(std::istream& in, std::ostream& out, CompositeShape& composite);
  std::istream& processInput(std::istream& in, std::ostream& out, CompositeShape& composite);
}

#endif
