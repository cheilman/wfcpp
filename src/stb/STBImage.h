//
// Created by Chris Heilman on 8/27/24.
//

#ifndef STBIMAGE_H
#define STBIMAGE_H
#include <memory>

#include "../wfc/Dimensions2D.h"
#include "../wfc/GridPosition.h"
#include "../wfc/Image.h"

class STBImage : public Image {
   public:
    typedef unsigned char PixelComponentType;

    STBImage(Dimensions2D size, int channels);
    STBImage(int width, int height, int channels);
    STBImage(PixelComponentType *data, int width, int height, int channels);
    virtual ~STBImage();

    static std::unique_ptr<Image> load(const std::string &path);
    virtual void save_png(const std::string &path) const;

    virtual int width() const { return this->_size.width(); }
    virtual int height() const { return this->_size.height(); }
    virtual Dimensions2D size() const { return this->_size; }
    virtual int channels() const { return this->_channels; }

    virtual std::unique_ptr<Image> cropy(GridPosition ul_corner, GridPosition br_corner) const;

    virtual void paste(const STBImage &src, GridPosition dest_ul_corner, bool with_alpha = false);
    virtual void paste(const Image &src, GridPosition dest_ul_corner, bool with_alpha = false);

   protected:
    int stride() const { return this->width() * this->_channels * sizeof(PixelComponentType); }

    void write_line(GridPosition dest_pos, const STBImage &source, GridPosition src_pos, int line_width, bool with_alpha);

    const PixelComponentType *data() const { return this->_data; }
    const PixelComponentType *data_at(GridPosition pos) const;
    PixelComponentType *writeable_data_at(GridPosition pos);

   private:
    PixelComponentType *_data;
    Dimensions2D _size;
    int _channels;
};

#endif  // STBIMAGE_H
