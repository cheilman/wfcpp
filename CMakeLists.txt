cmake_minimum_required(VERSION 3.29)
project(wfcpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(wfcpp
        src/main.cpp
        src/wfc/TileInfo.cpp
        src/wfc/TileInfo.h
        src/wfc/ImageSheet.cpp
        src/wfc/ImageSheet.h
        src/wfc/Dimensions2D.h
        src/wfc/GridPosition.h
        src/stb/stb.cpp
        src/stb/Image.cpp
        src/stb/Image.h
)
