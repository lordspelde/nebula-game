#include "tilemap.h"

#include <format>
#include <stdexcept>
#include <sstream>

Tilemap::Tilemap(int width, int height)
    : width{width}, height{height}, tiles(width * height) {
    if (width < 1) {
        throw std::runtime_error("width must be positive");
    }
    if (height < 1) {
        throw std::runtime_error("height must by positive");
    }
}

void Tilemap::check_bounds(int x, int y) const {
    if (x >= width || x < 0 || y >= height || y < 0) {
        throw std::runtime_error(std::format("({}, {}) is not within bounds ({}, {})", x, y, width, height));
    }
}

Tile& Tilemap::operator()(int x, int y) {
    check_bounds(x, y);
    return tiles.at(y*width + x);
}

const Tile& Tilemap::operator()(int x, int y) const {
    check_bounds(x, y);
    return tiles.at(y*width + x);
}
