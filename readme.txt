Coulor is a silly esoteric programming language I made, you program by making a bitmap image and and the intepreter will work it's way around the image, in a direction you can change and read its instructions from the pixels (by default from the red value of the pixels but you can change this.) It has basic memory and can output text and numbers.

Coulor is heavily inspired by Piet, but aims to be more flexable in both the ease of use and of the final images produced. Included are the spec and some example programs(images?)

To run download and compile (just run make, no external dependacies) and then call from terminal with image as first arg, example: "coulor.exe examples/helloworld.bmp"

Coulor is lincenced under Modified/Revised BSD License (http://opensource.org/licenses/bsd-license.php), but my intepreter uses the easybmp library by Paul Macklin/the EasyBMP Project which is also licended under the Modified/Revised BSD License. In essence, you are free to use, modify, and distribute this library in your personal, academic, and commerical applications so long as you retain the copyright and limited liability statements.
