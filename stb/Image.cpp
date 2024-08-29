//
// Created by Chris Heilman on 8/27/24.
//

#include "Image.h"

#include "stb_image.h"
#include "stb_image_write.h"

#include <assert.h>
#include <iostream>
#include <string>

Image::Image(const Dimensions2D size,
             const int channels) :
_data(static_cast<PixelComponentType *>(malloc(size.area() * channels * sizeof(PixelComponentType)))),
_size(size), _channels(channels)
{
  assert(this->_data != nullptr);
  memset(this->_data, 0, this->_size.area() * channels * sizeof(PixelComponentType));
}

Image::Image(const int width, const int height, const int channels)
  : Image(
    Dimensions2D(width, height), channels)
{}

Image::Image(PixelComponentType *data, const int width,
             const int height, const int channels) : _data(data), _size(width, height), _channels(channels) {
  assert(this->_data != nullptr);
}

Image::~Image() {
  if (this->_data != nullptr) {
    stbi_image_free(_data);
    this->_data = nullptr;
  }
}

std::unique_ptr<Image> Image::load(const std::string& filename) {
  int width, height, channels;
  PixelComponentType *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
  if (data == nullptr) {
    std::cerr << "Image Load Failure: " << stbi_failure_reason() << std::endl;
  }

  return std::make_unique<Image>(data, width, height, channels);
}

void Image::save_png(const std::string &path) const {
  stbi_write_png(path.c_str(), this->width(), this->height(), 4 /*RGBA*/, this->data(), this->stride());
}

const Image::PixelComponentType *Image::data_at(GridPosition pos) const {
  return this->data() + (pos.y() * this->stride()) + (pos.x() * this->channels() * sizeof(PixelComponentType));
}

Image::PixelComponentType *Image::writeable_data_at(GridPosition pos) {
  return this->_data + (pos.y() * this->stride()) + (pos.x() * this->channels() * sizeof(PixelComponentType));
}

void Image::write_line(GridPosition dest_pos, const Image &source, GridPosition src_pos, int line_width) {
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

  std::cerr << "Copying " << pixels_to_copy << "px (" << bytes_to_copy << "bytes) " <<
    "from " << src_pos << " to " << dest_pos << std::endl;

  memcpy(
    this->writeable_data_at(dest_pos),
    source.data_at(src_pos),
    bytes_to_copy
    );
}



std::unique_ptr<Image> Image::cropy(const GridPosition ul_corner,
                                    const GridPosition br_corner) const {
  const int dst_width = br_corner.x() - ul_corner.x() + 1;
  const int dst_height = br_corner.y() - ul_corner.y() + 1;

  assert(dst_width >= 1);
  assert(dst_height >= 1);

  auto dest = std::make_unique<Image>(dst_width, dst_height, this->channels());

  for (int dy = 0; dy < dst_height; dy++) {
    dest->write_line(GridPosition(0, dy), *this, GridPosition(ul_corner.x(), ul_corner.y() + dy), this->stride());
  }

  return std::move(dest);
}

void Image::paste(const Image &src, GridPosition dest_ul_corner) {
  const int src_width = std::min(src.width(), this->width() - dest_ul_corner.x()); // TODO: Need a +1/-1 here?
  const int src_height = std::min(src.height(), this->height() - dest_ul_corner.y()); // TODO: Need a +1/-1 here?
  assert(this->channels() == src.channels());

  for (int dy = 0; dy < src_height; dy++) {
    this->write_line(GridPosition(dest_ul_corner.x(), dest_ul_corner.y() + dy),
      src, GridPosition(0, dy), src_width);
  }
}
