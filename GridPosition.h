//
// Created by Chris Heilman on 8/27/24.
//

#ifndef GRID_POSITION_H
#define GRID_POSITION_H
#include <ostream>

class GridPosition {
public:
  GridPosition(const int x, const int y) : _x(x), _y(y) {}

  int x() const { return _x; }
  int y() const { return _y; }

  friend std::ostream& operator<<(std::ostream& os, const GridPosition& pos)
  {
    return os << "(" << pos.x() << ", " << pos.y() << ")";
  }

protected:
  int _x;
  int _y;
};



#endif //GRID_POSITION_H
