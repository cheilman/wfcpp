cmake_minimum_required(VERSION 3.29)
project(wfcpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(wfcpp main.cpp
        TileInfo.cpp
        TileInfo.h
        TileSheet.cpp
        TileSheet.h
        Dimensions2D.h
        GridPosition.h
        stb/stb.cpp
        stb/Image.cpp
        stb/Image.h)
