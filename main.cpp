#include "stb/Image.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string tiles_path = "/Users/cheilman/projects/wfcpp/resources/tilesets/mochii-plains/tilesetPlains.png";

    auto img = Image::load(tiles_path);
    std::cerr << "Loaded image: " << *img << std::endl;
    img->save_png("/Users/cheilman/tiles.png");

    auto section = img->cropy(GridPosition(16*5, 16*4), Dimensions2D(16,16));
    std::cerr << "Sectioned image: " << *section << std::endl;
    section->save_png("/Users/cheilman/section.png");

    img->paste(*section, GridPosition(32, 32));
    img->save_png("/Users/cheilman/overwritten.png");

    return 0;
}
