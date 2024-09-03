//
// Created by Chris Heilman on 9/3/24.
//

#include "TileSet.h"

TileSet::TileSet() {}

TileSet::TileSet(std::map<int, std::shared_ptr<Tile>> tiles) : _tiles(tiles) {
    for (auto it = this->_tiles.begin(); it != this->_tiles.end(); ++it) {
        this->_nameToId[it->second->name()] = it->second->id();
    }
}

void TileSet::add(std::shared_ptr<Tile> tile) {
    this->_tiles.emplace(tile->id(), tile);
    this->_nameToId[tile->name()] = tile->id();
}
void TileSet::add_from(std::map<GridPosition, TileInfo> tiles, const ImageSheet &sheet) {
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        const auto tile = std::make_shared<Tile>(it->second, sheet.load_subimage(it->first));
        this->add(tile);
    }
}

std::shared_ptr<Tile> TileSet::tile(int id) const {
    const auto tile = this->_tiles.find(id);

    if (tile == this->_tiles.end()) {
        return nullptr;
    }
    return tile->second;
}
std::shared_ptr<Tile> TileSet::tile(std::string name) const {
    const auto it = this->_nameToId.find(name);
    if (it == this->_nameToId.end()) {
        return nullptr;
    }
    return this->tile(it->second);
}