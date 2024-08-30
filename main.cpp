#include <iostream>

#include "stb/Image.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    // std::string prj_root = "/Users/cheilman/projects/wfcpp";
    // std::string out_root = "/Users/cheilman/";
    std::string prj_root = "C:/Users/chris/ClionProjects/wfcpp";
    std::string out_root = "C:/Users/chris/Desktop";

    std::string tiles_path = prj_root + "/resources/tilesets/mochii-plains/tilesetPlains.png";

    auto img = Image::load(tiles_path);
    std::cerr << "Loaded image: " << *img << std::endl;
    img->save_png(out_root + "/tiles.png");

    auto section = img->cropy(GridPosition(16 * 5, 16 * 4), Dimensions2D(16, 16));
    std::cerr << "Sectioned image: " << *section << std::endl;
    section->save_png(out_root + "/section.png");

    img->paste(*section, GridPosition(32, 32), true);
    img->save_png(out_root + "/overwritten.png");

    return 0;
}
