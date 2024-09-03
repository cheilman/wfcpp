//
// Created by Chris Heilman on 9/3/24.
//

#ifndef TILE_H
#define TILE_H
#include "../stb/Image.h"
#include "TileInfo.h"

class Tile {
   public:
    Tile(const TileInfo& tileInfo, const std::shared_ptr<Image>& image);
    ~Tile() = default;

    std::string name() const { return this->_info.name(); }
    int id() const { return this->_info.id(); }
    const TileInfo& tile_info() const { return this->_info; }
    const Image& image() const { return *this->_image; }

   private:
    TileInfo _info;
    std::shared_ptr<Image> _image;
};

#endif  // TILE_H
