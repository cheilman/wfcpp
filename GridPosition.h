//
// Created by Chris Heilman on 8/27/24.
//

#ifndef GRID_POSITION_H
#define GRID_POSITION_H



class GridPosition {
public:
  GridPosition(int x, int y) : _x(x), _y(y) {}

  int x() const { return _x; }
  int y() const { return _y; }

protected:
  int _x;
  int _y;
};



#endif //GRID_POSITION_H
