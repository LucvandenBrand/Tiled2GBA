#include <iostream>
#include "tileSetConverter.hpp"
#include "../../lib/lodepng/lodepng.h"
#include <algorithm>

TileSetConverter::TileSetConverter(const tmx::Tileset &tileSet) {
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, tileSet.getImagePath());

    if (error) {
        cout << "[ERR] Image decoding error " << error << ": " << lodepng_error_text(error) << endl;
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