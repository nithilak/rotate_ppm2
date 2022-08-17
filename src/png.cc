#include "png.hpp"

#include <fstream>
#include <stdexcept>
// #include <cstddef>
#include <iostream>

PNG::PNG(const std::string& filename, size_t width, size_t height) : width_(width), height_(height) {
    if (width < 0 || height < 0) {
      throw std::runtime_error("width and height cannot be less than 0");
    }
    std::ifstream ifs{filename};
    if (!ifs.good()) {
      throw std::runtime_error("file could not be opened");
    }
    int num = 0;
    try { //format check
      FormatCheckPpmNotConst(ifs);
    } catch (std::exception& e) {
        std::cout << "format error?" << std::endl;
        throw e;
    }
    size_t count = 0;
    for (size_t row = 0; row < height_; row++) {
      std::vector<Color> line;
      for (size_t col = 0; col < width_; col++) {
        int r, g, b = 0;
        ifs >> r >> g >> b;
        line.push_back(Color{r, g, b});
        count++;
      }
      image_.push_back(line);
    }
    const size_t kTotal = height_ * width_;
    if (count != kTotal) {
      throw std::runtime_error("count does not match: got " + std::to_string(count) + ", expected: " + std::to_string(kTotal));
    }
    ifs >> num;
    if (ifs.good()) {
      throw std::runtime_error("file has too many ints");
    }
}

void PNG::FormatCheckPpmNotConst(std::ifstream& ifs) {
    std::string line;
    std::getline(ifs, line);
    if (!ifs.good() || line != "P3") {
      throw std::runtime_error("format error");
    }
    int num = 0;
    ifs >> num;
    if (!ifs.good() || static_cast<size_t>(num) != width_) {
      throw std::runtime_error("incorrect width");
    }
    ifs >> num;
    if (!ifs.good() || static_cast<size_t>(num) != height_) {
      throw std::runtime_error("incorrect height");
    }
    ifs >> num;
    if (!ifs.good() || num != kMaxColorValue) { //these are both ints
      throw std::runtime_error("Max color value does not match");
    }
}


void PNG::ToPpm(const std::string& filename) {
    std::ofstream ofs{filename}; //caution, this rewrites the file everytime
    ofs << "P3\n" << width_ <<  " " << height_ << '\n' << kMaxColorValue << '\n';
    for (size_t row = 0; row < height_; row++) {
      for (size_t col = 0; col + 1 < width_; col++) {
        try {
          ofs << (image_.at(row).at(col)).ToString() << " "; //could be better
        } catch (std::exception& e) {
            std::cout << "ToPpm" << std::endl;
          throw e;
        }
      }
      ofs << (DatumAt(row, (width_ - 1))).ToString() << '\n';
    }
}

void PNG::RotateCounterClockwise() {
    std::vector<std::vector<Color>> image = image_;
    std::vector<std::vector<Color>> output(width_, std::vector<Color>(height_, Color{255, 0, 0}));
    image_ = output;
    Swap(height_, width_);
    std::cout << "width_: " << width_ << " height_: " << height_ <<std::endl;
    //translate each row to become a new col
    //reads the elements in order
    for (size_t row = 0; row < width_; row++) {
      Color color{0, 0, 0};
    //   std::vector<Color> line(height_, color);
      int current_width = static_cast<int>(height_) - 1;
      for (size_t col = 0; current_width >= 0; col++) {
        if (current_width < 0) {
          throw std::runtime_error("current_width is less than 0");
        }
        //put element in new row, starting from the bottom
        // Color color{0, 0, 0};
        // line.insert(line.begin(), color);
        // line.push_back(color);
        //could use a try block here instead of having expensive checks all of the time
        // try {
        std::cout << current_width << " " << row << " " << row << " " << col << std::endl;
        SetDatumAt(current_width, row, GetDatumAt(image, row, col));
        // GetDatumAt(output, (current_width), row) = DatumAt(row, col);

        // } catch (std::exception& e) {
        //   std::cout << "set" << std::endl;
        //   throw e;
        // }
        current_width--;
      }
    }
}

void PNG::FlipLeftDiagonal() {
    std::vector<std::vector<Color>> image = image_;
    std::vector<std::vector<Color>> output(width_, std::vector<Color>(height_, Color{255, 0, 0}));
    image_ = output;
    Swap(height_, width_);
    std::cout << "width_: " << width_ << " height_: " << height_ <<std::endl;
    //translate each row to become a new col
    //reads the elements in order
    for (size_t row = 0; row < width_; row++) {
      Color color{0, 0, 0};
    //   std::vector<Color> line(height_, color);
      int current_width = static_cast<int>(height_) - 1;
      int current_row = static_cast<int>(width_) - 1 - row;
      for (size_t col = 0; current_width >= 0 && current_row >= 0; col++) {
        if (current_width < 0) {
          throw std::runtime_error("current_width is less than 0");
        }
        if (current_row < 0) {
          throw std::runtime_error("current_row is less than 0");
        }
        //put element in new row, starting from the bottom
        // Color color{0, 0, 0};
        // line.insert(line.begin(), color);
        // line.push_back(color);
        //could use a try block here instead of having expensive checks all of the time
        // try {
        std::cout << current_width << " " << current_row << " " << row << " " << col << std::endl;
        SetDatumAt(current_width, current_row, GetDatumAt(image, row, col));
        // GetDatumAt(output, (current_width), row) = DatumAt(row, col);

        // } catch (std::exception& e) {
        //   std::cout << "set" << std::endl;
        //   throw e;
        // }
        current_width--;
      }
    }
}

void PNG::FlipAcrossAxisX() {
    std::vector<std::vector<Color>> image = image_;
    std::vector<std::vector<Color>> output(height_, std::vector<Color>(width_, Color{255, 0, 0}));
    image_ = output;
    // Swap(height_, width_);
    std::cout << "width_: " << width_ << " height_: " << height_ <<std::endl;
    //translate each row to become a new col
    //reads the elements in order
    for (size_t row = 0; row < height_; row++) {
      Color color{0, 0, 0};
    //   std::vector<Color> line(height_, color);
      int current_width = static_cast<int>(width_) - 1;
      int current_row = static_cast<int>(height_) - 1 - row;
      
      for (size_t col = 0; current_width >= 0 && current_row >= 0; col++) {
        if (current_width < 0) {
          throw std::runtime_error("current_width is less than 0");
        }
        if (current_row < 0) {
          throw std::runtime_error("current_row is less than 0");
        }
        //put element in new row, starting from the bottom
        // Color color{0, 0, 0};
        // line.insert(line.begin(), color);
        // line.push_back(color);
        //could use a try block here instead of having expensive checks all of the time
        // try {
        std::cout << current_width << " " << current_row << " " << row << " " << col << std::endl;
        SetDatumAt(current_row, current_width, GetDatumAt(image, row, col));
        // GetDatumAt(output, (current_width), row) = DatumAt(row, col);

        // } catch (std::exception& e) {
        //   std::cout << "set" << std::endl;
        //   throw e;
        // }
        current_width--;
      }
    }
}

void PNG::FlipAcrossAxisY() {
  FlipLeftDiagonal();
  RotateCounterClockwise();
}

void PNG::RotateClockwise() {
    std::vector<std::vector<Color>> image = image_;
    std::vector<std::vector<Color>> output(width_, std::vector<Color>(height_, Color{255, 0, 0}));
    image_ = output;
    Swap(height_, width_);
    std::cout << "width_: " << width_ << " height_: " << height_ <<std::endl;
    //translate each row to become a new col
    //reads the elements in order
    for (size_t row = 0; row < width_; row++) {
      Color color{0, 0, 0};
    //   std::vector<Color> line(height_, color);
      int current_width = 0;
      int current_row = static_cast<int>(width_) - 1 - row;
      for (size_t col = 0; current_width < static_cast<int>(height_) && current_row >= 0; col++) {
        if (current_width < 0) {
          throw std::runtime_error("current_width is less than 0");
        }
        if (current_width > static_cast<int>(height_)) {
          throw std::runtime_error("current_width is greater than \"static_cast<int>(height_)\"");
        }
        if (current_row < 0) {
          throw std::runtime_error("current_row is less than 0");
        }
        //put element in new row, starting from the bottom
        // Color color{0, 0, 0};
        // line.insert(line.begin(), color);
        // line.push_back(color);
        //could use a try block here instead of having expensive checks all of the time
        // try {
        std::cout << current_width << " " << current_row << " " << row << " " << col << std::endl;
        SetDatumAt(current_width, current_row, GetDatumAt(image, row, col));
        // GetDatumAt(output, (current_width), row) = DatumAt(row, col);

        // } catch (std::exception& e) {
        //   std::cout << "set" << std::endl;
        //   throw e;
        // }
        current_width++;
      }
    }
}

const Color& PNG::DatumAt(size_t row, size_t col) {
    if (row < 0 || row >= height_) {
      throw std::runtime_error("row is out of bounds: " + std::to_string(row));
    }
    if (col < 0 || col >= width_) {
      throw std::runtime_error("col is out of bounds: " + std::to_string(col));
    }
    return image_.at(row).at(col);
}

Color& PNG::GetDatumAt(std::vector<std::vector<Color>> image, size_t row, size_t col) {
    if (row < 0 || row >= image.size()) {
      throw std::runtime_error("getrow is out of bounds: " + std::to_string(row) + " " + std::to_string(image.size()));
    }
    if (col < 0 || col >= image.at(0).size()) {
      throw std::runtime_error("getcol is out of bounds: " + std::to_string(col));
    }
    Color& color = image.at(row).at(col);
    return color;
}

void PNG::SetDatumAt(size_t row, size_t col, const Color& color) {
    if (row < 0 || row >= height_) {
      throw std::runtime_error("setrow is out of bounds: " + std::to_string(row) + " " +  std::to_string(height_));
    }
    if (col < 0 || col >= width_) {
      throw std::runtime_error("setcol is out of bounds: " + std::to_string(col) + " " +  std::to_string(width_));
    }
    image_.at(row).at(col) = color;
}

void PNG::Swap(size_t& one, size_t& two) {
    size_t temp = one;
    one = two;
    two = temp;
}

