//
// Created by Chris Heilman on 9/4/24.
//

#include "SDLImage.h"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

#include <iostream>

SDLImage::SDLImage(SDL_Surface *surface) : _surface(surface) {}

SDLImage::~SDLImage() {
    if (this->_surface) {
        SDL_DestroySurface(this->_surface);
        this->_surface = nullptr;
    }
}

std::unique_ptr<Image> SDLImage::load(const std::string &path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cerr << "Error reading file from " << path << ". Err: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return std::make_unique<SDLImage>(surface);
}

void SDLImage::save_png(const std::string &path) const {
    if (!IMG_SavePNG(this->_surface, path.c_str())) {
        std::cerr << "Error saving file to " << path << ". Err: " << SDL_GetError() << std::endl;
    }
}

std::unique_ptr<Image> SDLImage::cropy(GridPosition ul_corner, GridPosition br_corner) const {
    int width = br_corner.x() - ul_corner.x();
    int height = br_corner.y() - ul_corner.y();

    SDL_Surface *dest = SDL_CreateSurface(width, height, this->surface()->format);
    if (dest == nullptr) {
        std::cerr << "Error creating surface for cropy: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Rect src_rect = {ul_corner.x(), ul_corner.y(), width, height};
    SDL_BlitSurface(this->surface(), &src_rect, dest, NULL);

    return std::make_unique<SDLImage>(dest);
}

void SDLImage::paste(const SDLImage &src, GridPosition dest_ul_corner, bool with_alpha) {
    SDL_Rect dstRect = dest_ul_corner.to_rect();
    SDL_BlitSurface(src.surface(), NULL, this->_surface, &dstRect);
}

void SDLImage::paste(const Image &src, GridPosition dest_ul_corner, bool with_alpha) {
    // TODO
}

SDL_Texture *SDLImage::to_texture(SDL_Renderer &renderer) const {
    auto tex = SDL_CreateTextureFromSurface(&renderer, this->_surface);
    if (tex == nullptr) {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
    }
    return tex;
}

std::pair<SDL_Window*, SDL_Renderer*> SDLImage::display() const  {
    int scale = 1024 / this->height();

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "An image!");
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, this->width() * scale);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, this->height() * scale);

    auto window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);

    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        return std::pair<SDL_Window*, SDL_Renderer*>(nullptr, nullptr);
    }

    auto renderer = SDL_CreateRenderer(window, "software");
    if (!renderer) {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return std::pair<SDL_Window*, SDL_Renderer*>(nullptr, nullptr);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    this->display_on(*renderer);
    SDL_RenderPresent(renderer);

    return std::pair(window, renderer);
}


void SDLImage::display_on(SDL_Renderer &renderer) const {
    auto tex = this->to_texture(renderer);
    if (tex == nullptr) {
        return;
    }

    if (!SDL_RenderTexture(&renderer, tex, nullptr, nullptr)) {
        std::cerr << "Error rendering texture: " << SDL_GetError() << std::endl;
    }

    SDL_DestroyTexture(tex);
}
