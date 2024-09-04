//
// Created by Chris Heilman on 9/4/24.
//

#ifndef SDLIMAGE_H
#define SDLIMAGE_H
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

#include <string>

#include "Dimensions2D.h"
#include "Image.h"

class SDLImage : public Image {
   public:
    explicit SDLImage(SDL_Surface *surface);  // NOTE: Takes ownership
    ~SDLImage() override;

    static std::unique_ptr<Image> load(const std::string &path);
    void save_png(const std::string &path) const override;

    int width() const override { return this->_surface->w; }
    int height() const override { return this->_surface->h; }
    Dimensions2D size() const override { return Dimensions2D(this->width(), this->height()); }

    std::unique_ptr<Image> cropy(GridPosition ul_corner, GridPosition br_corner) const override;

    virtual void paste(const SDLImage &src, GridPosition dest_ul_corner, bool with_alpha = false);
    void paste(const Image &src, GridPosition dest_ul_corner, bool with_alpha = false) override;

    void display_on(SDL_Renderer &renderer) const override;

    friend std::ostream &operator<<(std::ostream &os, const SDLImage &img) {
        return os << "SDLImage(" << img.size() << ", format " << img.pixel_format_str() << ")";
    }

   protected:
    const SDL_PixelFormatDetails *pixel_format() const { return SDL_GetPixelFormatDetails(this->_surface->format); }
    std::string pixel_format_str() const { return SDL_GetPixelFormatName(this->_surface->format); }

    SDL_Surface *surface() const { return this->_surface; }
    SDL_Texture *to_texture(SDL_Renderer &renderer) const;

   private:
    SDL_Surface *_surface;
};

#endif  // SDLIMAGE_H
