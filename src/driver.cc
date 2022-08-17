#include <iostream>

#include "png.hpp"
#include "color.hpp"

int main() {
    std::cout << "Hello, world!" << std::endl;

    PNG png("/Users/nithilak/png-test2/examples/test.ppm", 5, 3);
    png.RotateCounterClockwise();
    // png.RotateClockwise();
    //careful, this rewrites the file every time
    png.ToPpm("/Users/nithilak/png-test2/examples_output/test_output.ppm");
    
    png.FlipHorizontally();
    png.ToPpm("/Users/nithilak/png-test2/examples_output/test_output_2.ppm");
}