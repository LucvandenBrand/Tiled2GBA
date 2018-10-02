#include <iostream>
#include "tileSetConverter.hpp"
#include "../../lib/lodepng/lodepng.h"
#include "../../log/logger.hpp"
#include "image/image.hpp"
#include "imageRetiler/imageRetiler.hpp"
#include "../../gba/background.h"
#include "terrainConverter/terrainConverter.hpp"
#include <algorithm>

TileSetConverter::TileSetConverter(const tmx::Tileset &tileSet) {
    auto log = *Logger::getInstance();

    auto tileSize = tileSet.getTileSize().x;
    TerrainConverter terrainConverter(tileSize);
    d_terrainMapBytes = terrainConverter.convertTerrainMap(tileSet.getTiles());

    Color transparentColor = tmxColourToColor(tileSet.getTransparencyColour());
    generateColorTile(transparentColor);

    try {
        Image image(tileSet.getImagePath());
        parseSheet(image, tileSize);
    } catch (runtime_error &error) {
        log(ERROR, error.what());
        exit(EXIT_FAILURE);
    }
}

vector<uint16_t> TileSetConverter::getTiles() {
    return d_tileBytes;
}

vector<uint16_t> TileSetConverter::getPalette() {
    return d_paletteBytes;
}

vector<uint16_t> TileSetConverter::getTerrainMap() {
    return d_terrainMapBytes;
}

uint8_t TileSetConverter::remap(uint8_t byte, uint8_t max, uint8_t newMax) {
    float ratio = 1.0f * byte / max;
    return (uint8_t) (ratio * newMax);
}

uint8_t TileSetConverter::addColor(Color color) {
    uint16_t gbaColor = 0;
    gbaColor |= remap(color.red,   0x00FF, 0x001F);
    gbaColor |= remap(color.green, 0x00FF, 0x001F) << 5u;
    gbaColor |= remap(color.blue,  0x00FF, 0x001F) << 10u;

    auto colorIterator = find(d_paletteBytes.begin(), d_paletteBytes.end(), gbaColor);
    if(colorIterator != d_paletteBytes.end()) {
        auto index = std::distance(d_paletteBytes.begin(), colorIterator);
        return (uint8_t) index;
    }

    d_paletteBytes.push_back(gbaColor);
    return (uint8_t) (d_paletteBytes.size() - 1);
}

Color TileSetConverter::tmxColourToColor(tmx::Colour colour) {
    Color color;
    color.red   = colour.r;
    color.green = colour.g;
    color.blue  = colour.b;
    color.alpha = colour.a;
    return color;
}

void TileSetConverter::parseSheet(Image image, unsigned tileSize) {
    ImageRetiler retiler;
    Image retiledImage = retiler.retile(image, tileSize);

    if (tileSize != GBA_TILE_SIZE)
        retiledImage = retiler.retile(retiledImage, GBA_TILE_SIZE);

    d_tileBytes.reserve(retiledImage.getWidth() * retiledImage.getHeight() / 2);
    for (unsigned row = 0; row < retiledImage.getHeight(); row++) {
        for (unsigned col = 0; col < retiledImage.getWidth(); col += 2) {
            Color firstColor   = retiledImage.getPixel(row, col);
            uint8_t firstPixel = addColor(firstColor);

            Color secondColor   = retiledImage.getPixel(row, col + 1);
            uint8_t secondPixel = addColor(secondColor);

            d_tileBytes.push_back(combinePixels(firstPixel, secondPixel));
        }
    }

    d_paletteBytes.resize(PALETTE_COLORS, 0x0000);
}

void TileSetConverter::generateColorTile(const Color &color) {
    uint8_t pixel = addColor(color);
    for (unsigned row = 0; row < GBA_TILE_SIZE; row++) {
        for (unsigned col = 0; col < GBA_TILE_SIZE; col += 2) {
            d_tileBytes.push_back(combinePixels(pixel, pixel));
        }
    }
}

uint16_t TileSetConverter::combinePixels(uint8_t firstPixel, uint8_t secondPixel) {
    return firstPixel | (secondPixel << 8);
}