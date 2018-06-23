#include <iostream>
#include "tileSetConverter.hpp"
#include "../../lib/lodepng/lodepng.h"
#include "../../log/logger.hpp"
#include <algorithm>

TileSetConverter::TileSetConverter(const tmx::Tileset &tileSet) {
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, tileSet.getImagePath());

    auto log = *Logger::getInstance();
    if (error) {
        log(ERROR, "Tile set image decoding error " + to_string(error) + ": " + lodepng_error_text(error));
        exit(EXIT_FAILURE);
    }

    if (width != GBA_TILE_SIZE) {
        log(ERROR, "The tile set image must be 8 pixels wide.");
        exit(EXIT_FAILURE);
    }

    if (height % GBA_TILE_SIZE != 0) {
        log(ERROR, "The tile set image must have a height that is a multiple of 8.");
        exit(EXIT_FAILURE);
    }

    auto tileSize = tileSet.getTileSize();
    parseSheet(image, width, height, tileSize.x, tileSize.y);
}

vector<uint16_t> TileSetConverter::getTiles() {
    return d_tileBytes;
}

vector<uint16_t> TileSetConverter::getPalette() {
    return d_paletteBytes;
}

unsigned char TileSetConverter::remap(unsigned char byte, unsigned char max, unsigned char newMax) {
    float ratio = 1.0f * byte / max;
    return (unsigned char) (ratio * newMax);
}

uint8_t TileSetConverter::addColor(unsigned char red, unsigned char green, unsigned char blue) {
    uint16_t color = 0;
    color |= remap(red,   0x00FF, 0x001F);
    color |= remap(green, 0x00FF, 0x001F) << 5u;
    color |= remap(blue,  0x00FF, 0x001F) << 10u;

    auto colorIterator = find(d_paletteBytes.begin(), d_paletteBytes.end(), color);
    if(colorIterator != d_paletteBytes.end()) {
        auto index = std::distance(d_paletteBytes.begin(), colorIterator);
        return (uint8_t) index;
    }

    d_paletteBytes.push_back(color);
    return (uint8_t) (d_paletteBytes.size() - 1);
}

void TileSetConverter::parseSheet(const vector<unsigned char> &sheet, unsigned sheetWidth, unsigned sheetHeight,
                                  unsigned tileWidth, unsigned tileHeight) {
    addColor(0, 0, 0);

    for (int index = 0; index < sheet.size(); index += 8) {
        unsigned char red   = sheet[index];
        unsigned char green = sheet[index + 1];
        unsigned char blue  = sheet[index + 2];
        uint8_t firstPixel = addColor(red, green, blue);

        red   = sheet[index + 4];
        green = sheet[index + 5];
        blue  = sheet[index + 6];
        uint8_t secondPixel = addColor(red, green, blue);

        uint16_t pixel = secondPixel | (firstPixel << 8);
        d_tileBytes.push_back(pixel);
    }

    d_paletteBytes.resize(PALETTE_COLORS, 0x0000);
}