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
    
    png.FlipAcrossAxisX();
    png.ToPpm("/Users/nithilak/png-test2/examples_output/test_output_2.ppm");

    png.RotateClockwise();
    png.ToPpm("/Users/nithilak/png-test2/examples_output/test_output_3.ppm");

    png.FlipAcrossAxisY();
    png.ToPpm("/Users/nithilak/png-test2/examples_output/test_output_4.ppm");

    png.FlipLeftDiagonal();
    png.ToPpm("/Users/nithilak/png-test2/examples_output/test_output_5.ppm");

    png.FlipRightDiagonal();
    png.ToPpm("/Users/nithilak/png-test2/examples_output/test_output_5.ppm");
    
}