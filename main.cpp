#include <iostream>

#include "ImageSheet.h"
#include "stb/Image.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string prj_root = "/Users/cheilman/CLionProjects/wfcpp";
    std::string out_root = "/Users/cheilman/";
    // std::string prj_root = "C:/Users/chris/ClionProjects/wfcpp";
    // std::string out_root = "C:/Users/chris/Desktop";

    std::string tiles_path = prj_root + "/resources/tilesets/mochii-plains/tilesetPlains.png";

    auto sheet = ImageSheet::load(tiles_path, Dimensions2D(16, 16));
    std::cerr << "Loaded image sheet: " << *sheet << std::endl;
    sheet->sheet().save_png(out_root + "/tiles.png");

    auto tile = sheet->load_subimage(GridPosition(5, 4));
    std::cerr << "Sectioned image: " << *tile << std::endl;
    tile->save_png(out_root + "/section.png");

    return 0;
}
