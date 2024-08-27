//
// Created by Chris Heilman on 8/27/24.
//

#ifndef DIMENSIONS2D_H
#define DIMENSIONS2D_H



class Dimensions2D {
public:
  Dimensions2D(int width, int height) : _width(width), _height(height) {}

  int width() const { return _width; }
  int height() const { return _height; }

protected:
  int _width;
  int _height;
};



#endif //DIMENSIONS2D_H
