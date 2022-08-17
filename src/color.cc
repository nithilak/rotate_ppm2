#include "color.hpp"

Color::Color(int r, int g, int b) : r_(r), g_(g), b_(b) {
    CheckRange(r);
    CheckRange(g);
    CheckRange(b);
}

std::string Color::ToString() const {
    return std::to_string(r_)+ " " + std::to_string(g_) + " " + std::to_string(b_);
}

void Color::CheckRange(int c) {
  if (!(0 <= c && c <= kMaxColorValue)) {
    throw std::runtime_error("color out of range: " + ToString());
  }
}
