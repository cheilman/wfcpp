//
// Created by Chris Heilman on 9/3/24.
//

#ifndef TILESET_H
#define TILESET_H
#include <map>

#include "ImageSheet.h"
#include "Tile.h"

class TileSet {
   public:
    TileSet();
    explicit TileSet(std::map<int, std::shared_ptr<Tile>> tiles);
    ~TileSet() = default;

    void add(std::shared_ptr<Tile> tile);
    void add_from(std::map<GridPosition, TileInfo> tiles, const ImageSheet &sheet);

    std::shared_ptr<Tile> tile(int id) const;
    std::shared_ptr<Tile> tile(std::string name) const;

   private:
    std::map<int, std::shared_ptr<Tile>> _tiles;
    std::map<std::string, int> _nameToId;
};

#endif  // TILESET_H
