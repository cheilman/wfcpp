//
// Created by Chris Heilman on 8/27/24.
//

#ifndef IMAGESHEET_H
#define IMAGESHEET_H
#include <string>
#include "Image.h"

#include "Dimensions2D.h"

class ImageSheet {
   public:
    ImageSheet(std::unique_ptr<Image> sheet, Dimensions2D subimage_size);
    virtual ~ImageSheet() = default;

    const Dimensions2D &subimage_size() const { return this->_subimage_size; }
    const Image &sheet() const { return *this->_sheet; }

    virtual std::shared_ptr<Image> load_subimage(GridPosition position) const;

    static std::unique_ptr<ImageSheet> load(const std::string &filename, Dimensions2D subimage_size);

    friend std::ostream &operator<<(std::ostream &os, const ImageSheet &sheet) {
        return os << "ImageSheet("
                  << "sub size = " << sheet._subimage_size << ", sheet = " << *sheet._sheet << ")";
    }

   private:
    std::unique_ptr<Image> _sheet;
    Dimensions2D _subimage_size;
};

#endif  // IMAGESHEET_H
