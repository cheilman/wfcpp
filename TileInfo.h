//
// Created by Chris Heilman on 8/27/24.
//

#ifndef TILEINFO_H
#define TILEINFO_H

#include <string>

class TileInfo {
public:
    explicit TileInfo(std::string name);
    virtual ~TileInfo() = default;

    std::string name() const { return this->_name; }
    int id() const { return this->_id; }

protected:
    int _id;
    std::string _name;
};

#endif //TILEINFO_H
