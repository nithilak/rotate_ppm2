#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

class Color {
    public:
    Color(int r, int g, int b);
    std::string ToString() const;
    // Color(const Color& color) = default;

    // Color& operator=(const Color& color) = default;

    //helpers
    void CheckRange(int c);

    private:
    int r_;
    int g_;
    int b_;
    int kMaxColorValue = 255; //this is const, but then stuff happens
};

#endif