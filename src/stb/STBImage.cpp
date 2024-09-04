//
// Created by Chris Heilman on 8/27/24.
//

#include "STBImage.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include "stb_image.h"
#include "stb_image_write.h"

STBImage::STBImage(const Dimensions2D size, const int channels)
    : _data(static_cast<PixelComponentType *>(malloc(size.area() * channels * sizeof(PixelComponentType)))),
      _size(size),
      _channels(channels) {
    assert(this->_data != nullptr);
    memset(this->_data, 0, this->_size.area() * channels * sizeof(PixelComponentType));
}

STBImage::STBImage(const int width, const int height, const int channels)
    : STBImage(Dimensions2D(width, height), channels) {}

STBImage::STBImage(PixelComponentType *data, const int width, const int height, const int channels)
    : _data(data), _size(width, height), _channels(channels) {
    assert(this->_data != nullptr);
}

STBImage::~STBImage() {
    if (this->_data != nullptr) {
        stbi_image_free(_data);
        this->_data = nullptr;
    }
}

std::unique_ptr<Image> STBImage::load(const std::string &filename) {
    int width, height, channels;
    PixelComponentType *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (data == nullptr) {
        std::cerr << "STBImage Load Failure: " << stbi_failure_reason() << std::endl;
    }

    return std::make_unique<STBImage>(data, width, height, channels);
}

void STBImage::save_png(const std::string &path) const {
    stbi_write_png(path.c_str(), this->width(), this->height(), 4 /*RGBA*/, this->data(), this->stride());
}

const STBImage::PixelComponentType *STBImage::data_at(GridPosition pos) const {
    return this->data() + (pos.y() * this->stride()) + (pos.x() * this->channels() * sizeof(PixelComponentType));
}

STBImage::PixelComponentType *STBImage::writeable_data_at(GridPosition pos) {
    return this->_data + (pos.y() * this->stride()) + (pos.x() * this->channels() * sizeof(PixelComponentType));
}

void STBImage::write_line(GridPosition dest_pos, const STBImage &source, GridPosition src_pos, int line_width,
                          bool with_alpha) {
    assert(this->channels() == source.channels());
    assert(line_width >= 0);
    if (line_width == 0) {
        return;
    }

    int pixels_to_copy = line_width;
    // Don't pull too many
    pixels_to_copy = std::min(pixels_to_copy, (source.width() - src_pos.x()));  // TODO: Need +1/-1?
    // Don't push too many
    pixels_to_copy = std::min(pixels_to_copy, (this->width() - dest_pos.x()));  // TODO: Need +1/-1?

    int bytes_to_copy = pixels_to_copy * this->channels() * sizeof(PixelComponentType);

    std::cerr << "Copying " << pixels_to_copy << "px (" << bytes_to_copy << "bytes) "
              << "from " << src_pos << " to " << dest_pos << std::endl;

    // If we don't care about alpha, there is only one channel (monochrome), or
    // three channels (RGB) just do an easy memcpy
    if ((!with_alpha) || (this->channels() == 1) || (this->channels() == 3)) {
        memcpy(this->writeable_data_at(dest_pos), source.data_at(src_pos), bytes_to_copy);
    } else {
        // Do a pixel-by-pixel copy, checking the alpha channel
        for (int dx = 0; dx < pixels_to_copy; dx++) {
            const PixelComponentType *src = source.data_at(GridPosition(src_pos.x() + dx, src_pos.y()));
            PixelComponentType alpha = src[this->channels() - 1];

            // TODO: Fix blending, right now it's all or nothing
            if (alpha == 0) {
                // Transparent, skip it
                continue;
            }

            memcpy(this->writeable_data_at(GridPosition(dest_pos.x() + dx, dest_pos.y())), src,
                   this->channels() * sizeof(PixelComponentType));
        }
    }
}

std::unique_ptr<Image> STBImage::cropy(const GridPosition ul_corner, const GridPosition br_corner) const {
    const int dst_width = br_corner.x() - ul_corner.x() + 1;
    const int dst_height = br_corner.y() - ul_corner.y() + 1;

    assert(dst_width >= 1);
    assert(dst_height >= 1);

    auto dest = std::make_unique<STBImage>(dst_width, dst_height, this->channels());

    for (int dy = 0; dy < dst_height; dy++) {
        dest->write_line(GridPosition(0, dy), *this, GridPosition(ul_corner.x(), ul_corner.y() + dy), this->stride(),
                         false);
    }

    return dest;
}

void STBImage::paste(const Image &src, GridPosition dest_ul_corner, bool with_alpha) {
    // TODO
}

void STBImage::paste(const STBImage &src, GridPosition dest_ul_corner, bool with_alpha) {
    const int src_width = std::min(src.width(),
                                   this->width() - dest_ul_corner.x());
    const int src_height = std::min(src.height(),
                                    this->height() - dest_ul_corner.y());
    assert(this->channels() == src.channels());

    for (int dy = 0; dy < src_height; dy++) {
        this->write_line(GridPosition(dest_ul_corner.x(), dest_ul_corner.y() + dy), src, GridPosition(0, dy), src_width,
                         with_alpha);
    }
}
