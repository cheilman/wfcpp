//
// Created by Chris Heilman on 8/27/24.
//

#include "ImageSheet.h"

#include <cassert>

#include "SDLImage.h"

ImageSheet::ImageSheet(std::unique_ptr<Image> sheet, Dimensions2D subimage_size)
    : _sheet(std::move(sheet)), _subimage_size(subimage_size) {
    assert(_sheet != nullptr);
}

std::unique_ptr<ImageSheet> ImageSheet::load(const std::string &filename, Dimensions2D subimage_size) {
    auto img = SDLImage::load(filename);
    if (img == nullptr) {
        return nullptr;
    }

    return std::make_unique<ImageSheet>(std::move(img), subimage_size);
}

std::shared_ptr<Image> ImageSheet::load_subimage(GridPosition position) const {
    const GridPosition ul(position.x() * this->_subimage_size.width(), position.y() * this->_subimage_size.height());
    const GridPosition br(ul.x() + this->_subimage_size.width(), ul.y() + this->_subimage_size.height());

    auto uniq = this->_sheet->cropy(ul, br);
    if (uniq == nullptr) {
        return nullptr;
    }

    return std::move(uniq);
}