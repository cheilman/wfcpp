//
// Created by Chris Heilman on 9/3/24.
//

#include "Tile.h"

Tile::Tile(const TileInfo& tileInfo, const std::shared_ptr<Image>& image) : _info(tileInfo), _image(image) {}