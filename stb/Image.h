//
// Created by Chris Heilman on 8/27/24.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <memory>

class Image {
public:
  Image(unsigned char *data, unsigned int width, unsigned int height, unsigned int channels);
  static std::unique_ptr<Image> load(const std::string& path);

  ~Image();

  int width() const { return _width; }
  int height() const { return _height; }
  int channels() const { return _channels; }
protected:
private:
  unsigned char *_data;
  int _width, _height;
  int _channels;
};



#endif //IMAGE_H
