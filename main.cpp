#include <iostream>
#include "header.h"

using namespace cimg_library;

int main(int argc, char* argv[])
{
if (argc < 4 || argc > 5) { std::cerr << "Usage: ImageToTerminalClean <path_to_image> <x_symbol_count> <y_symbol_count>\n"; return 1;}
std::cout << "Hello World!\n";

try {
    CImg<unsigned char> img(argv[1]);
    const int symbol_res[] = { std::stoi(argv[2]), std::stoi(argv[3]) };

    int* char_px = ResolutionResolver(img.width(), img.height(), symbol_res); // The amount of pixels a character represents
    std::cout << img.width() << " " << img.height() << " " << char_px << " \n ";

    // Retrieving the grayscale value based on the NTSC luminance formula, as well as the opacity, to calculate brightness values to match with symbols
    // Iterating through the image in character sized blocks
    for (int y_block = 0; y_block < img.height(); y_block += char_px[1]) {
        for (int x_block = 0; x_block < img.width(); x_block += char_px[0]) {
            double total_block_brightness = 0;
            // Iterating through the image block
            for (int y = 0; y < char_px[1]; ++y) {
                if (y_block + y > img.height()-1) break; // Doesn't handle the issue that block_brightness_level will not be accurate because of divison by char_px size
                for (int x = 0; x < char_px[0]; ++x) {
                    if (x_block + x > img.width()-1) break;
                    int r = static_cast<int>(img(x_block + x, y_block + y, 0));
                    int g = static_cast<int>(img(x_block + x, y_block + y, 1));
                    int b = static_cast<int>(img(x_block + x, y_block + y, 2));
                    int a = 255; // I do not understand why I cannot read the opacity channel consistently - it has a random chance of crashing with a read access violation
                    //try { a = static_cast<int>(img(x_block + x, y_block + y, 3)); }
                    //catch (...) { continue; }
                    total_block_brightness += ((0.299 * r + 0.587 * g + 0.114 * b) * (a/255.0));
                }
            }
            double block_brightness_level = total_block_brightness / (char_px[0] * char_px[1] * 255); // 255 to get the relative value in %
            std::cout << ascii_brightness[CorrespondingSymbol(block_brightness_level)];
        }
        std::cout << std::endl;
    }
    delete char_px;
    return 0;
}
catch (CImgIOException& e) {
    std::cerr << "Error loading image: " << e.what() << std::endl;
    return 1;
}
}
