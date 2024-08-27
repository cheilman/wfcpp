//
// Created by Chris Heilman on 8/27/24.
//

#include "Image.h"

#include "stb_image.h"

#include <assert.h>
#include <string>

Image::Image(unsigned char *data, unsigned int width, unsigned int height, unsigned int channels) : _data(data), _width(width), _height(height), _channels(channels) {
  assert(data != nullptr);
}
static std::unique_ptr<Image> load(const std::string& filename) {
  int width, height, channels;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

  return std::make_unique<Image>(data, width, height, channels);
}

Image::~Image() {
  if (this->_data != nullptr) {
    stbi_image_free(_data);
    this->_data = nullptr;
  }
}