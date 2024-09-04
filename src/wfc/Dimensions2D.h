//
// Created by Chris Heilman on 8/27/24.
//

#ifndef DIMENSIONS2D_H
#define DIMENSIONS2D_H
#include <SDL3/SDL_rect.h>

#include <ostream>

class Dimensions2D {
   public:
    Dimensions2D(const int width, const int height) : _width(width), _height(height) {}

    int width() const { return this->_width; }
    int height() const { return this->_height; }
    int area() const { return this->_width * this->_height; }

    SDL_Rect to_rect() const { return SDL_Rect{0, 0, this->_width, this->_height}; }

    friend std::ostream& operator<<(std::ostream& os, const Dimensions2D& dims) {
        return os << dims.width() << "x" << dims.height();
    }

   protected:
    int _width;
    int _height;
};

#endif  // DIMENSIONS2D_H
