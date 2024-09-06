//
// Created by Chris Heilman on 9/4/24.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <SDL3/SDL_render.h>
#include <memory>

#include "Dimensions2D.h"
#include "GridPosition.h"

class Image {
   public:
    virtual ~Image() = default;

    virtual void save_png(const std::string &path) const = 0;

    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual Dimensions2D size() const = 0;

    virtual std::unique_ptr<Image> cropy(GridPosition ul_corner, GridPosition br_corner) const = 0;
    std::unique_ptr<Image> cropy(const GridPosition ul_corner, const Dimensions2D dims) const {
        return this->cropy(ul_corner,
                           GridPosition(ul_corner.x() + dims.width() - 1, ul_corner.y() + dims.height() - 1));
    }

    virtual void paste(const Image &src, GridPosition dest_ul_corner, bool with_alpha = false) = 0;

    virtual std::pair<SDL_Window*, SDL_Renderer*> display() const { return std::pair<SDL_Window*, SDL_Renderer*>(nullptr, nullptr); }
    virtual void display_on(SDL_Renderer &renderer) const {}

    friend std::ostream &operator<<(std::ostream &os, const Image &img) { return os << "Image(" << img.size() << ")"; }
};

#endif  // IMAGE_H
