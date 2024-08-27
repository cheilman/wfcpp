#include <atomic>
#include <utility>
#include "TileInfo.h"

static std::atomic<int> NextTileId(0);

TileInfo::TileInfo(std::string name) : _id(NextTileId.fetch_add(1)), _name(std::move(name)) {
}
