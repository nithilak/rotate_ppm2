#ifndef PNG_HPP
#define PNG_HPP

#include "color.hpp"

#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

class PNG {
  public:
  PNG(const std::string& filename, size_t width, size_t height);
  void RotateCounterClockwise();
  void RotateClockwise();
  void ToPpm(const std::string& filename);
  void FormatCheckPpmNotConst(std::ifstream& ifs);
  Color& GetDatumAt(std::vector<std::vector<Color>> image, size_t row, size_t col);
  const Color& DatumAt(size_t row, size_t col);
  void SetDatumAt(size_t row, size_t col, const Color& color);
  void Swap(size_t& one, size_t& two);
  // void RotateClockwise() was intended, but FlipHorizontally()
  void FlipLeftDiagonal(); //old FlipHorizontally moved to here
  // void FlipHorizontally(); //actually FlipLeftDiagonal at first
  void FlipAcrossAxisX(); // FlipHorizontally renamed to make it clearer
  void FlipAcrossAxisY(); //more clear
  void FlipRightDiagonal(); //just because, to complete the set

  private:
  std::vector<std::vector<Color>> image_;
  size_t width_;
  size_t height_;
  const int kMaxColorValue = 255;

};

// PNG(const std::string& filename, size_t width, size_t height) {

// }

#endif