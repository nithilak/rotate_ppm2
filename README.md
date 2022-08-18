# rotate_ppm2
How to use:
Create a PNG object in driver.cc, and use as you wish. It can be then flipped and rotated, and there are also some helper funtions but they are mostly irrelevant for your purposes, unless you want to set/get a specific spot of color. The color class can also be useful too, if you want to test out new colors and put them in a specific spot.

Excecute: make exec

then: bin/exec

to see the final results.

Note: the ToPpm function will rewrite the destination file every single time. If I could add a popup here, I would. But that is really complicated and I don't know how to do that, and it's probably fine as it is now so for now, I will let it be as it is(with no warning aside from in writing beforehand).

Flips an image with the .ppm format in all rotations, flips, and additionally it flips on both diagonals too.
Note: the maximum color range specified is 0-255 inclusive on both ends.
