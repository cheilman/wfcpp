//
// Created by Chris Heilman on 8/27/24.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <memory>

#include "../Dimensions2D.h"
#include "../GridPosition.h"

class Image {
   public:
    typedef unsigned char PixelComponentType;

    Image(Dimensions2D size, int channels);
    Image(int width, int height, int channels);
    Image(PixelComponentType *data, int width, int height, int channels);
    ~Image();

    static std::unique_ptr<Image> load(const std::string &path);
    void save_png(const std::string &path) const;

    int width() const { return this->_size.width(); }
    int height() const { return this->_size.height(); }
    Dimensions2D size() const { return this->_size; }
    int channels() const { return this->_channels; }

    std::unique_ptr<Image> cropy(GridPosition ul_corner, GridPosition br_corner) const;
    std::unique_ptr<Image> cropy(const GridPosition ul_corner, const Dimensions2D dims) const {
        return this->cropy(ul_corner,
                           GridPosition(ul_corner.x() + dims.width() - 1, ul_corner.y() + dims.height() - 1));
    }

    void paste(const Image &src, GridPosition dest_ul_corner, bool with_alpha = false);

    friend std::ostream &operator<<(std::ostream &os, const Image &img) {
        return os << "Image(" << img.size() << ", " << img.channels() << " channels)";
    }

   protected:
    int stride() const { return this->width() * this->_channels * sizeof(PixelComponentType); }

    void write_line(GridPosition dest_pos, const Image &source, GridPosition src_pos, int line_width, bool with_alpha);

    const PixelComponentType *data() const { return this->_data; }
    const PixelComponentType *data_at(GridPosition pos) const;
    PixelComponentType *writeable_data_at(GridPosition pos);

   private:
    PixelComponentType *_data;
    Dimensions2D _size;
    int _channels;
};

#endif  // IMAGE_H
