cmake_minimum_required(VERSION 3.29)
project(wfcpp
        VERSION 0.1
        LANGUAGES C CXX
)
if(APPLE)
    enable_language(OBJC)
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable Shared Libs
set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)

# Disable AVIF Support
set(SDL3IMAGE_AVIF OFF)

# Enable FetchContent
include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG origin/main
        OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
        SDL3_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG origin/main
        OVERRIDE_FIND_PACKAGE
)

set(SDL3IMAGE_INSTALL OFF)
set(SDL3IMAGE_BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(SDL3_image)

#include(FetchContent)
#
#FetchContent_Declare(
#        Boost
#        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
#        URL_MD5 893b5203b862eb9bbd08553e24ff146a
#        DOWNLOAD_EXTRACT_TIMESTAMP ON
#        EXCLUDE_FROM_ALL
#)
#
#set(BOOST_INCLUDE_LIBRARIES container_hash)
#FetchContent_MakeAvailable(Boost)

add_executable(wfcpp
        src/main.cpp
        src/wfc/TileInfo.cpp
        src/wfc/TileInfo.h
        src/wfc/ImageSheet.cpp
        src/wfc/ImageSheet.h
        src/wfc/Dimensions2D.h
        src/wfc/GridPosition.h
        src/wfc/Tile.cpp
        src/wfc/Tile.h
        src/wfc/TileSet.cpp
        src/wfc/TileSet.h
        src/wfc/SDLImage.cpp
        src/wfc/SDLImage.h
        src/wfc/Image.h
)

# Link SDL3 and SDL3_image to our demo app
target_include_directories(wfcpp PUBLIC SDL3::Headers SDL3_image::Headers)
target_link_libraries(wfcpp PUBLIC SDL3::SDL3-static SDL3_image::SDL3_image-static)
