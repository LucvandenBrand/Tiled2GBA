#include <iostream>
#include "tileSetConverter.h"
#include "../lib/lodepng/lodepng.h"
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

uint16_t TileSetConverter::addColor(unsigned char red, unsigned char green, unsigned char blue) {
    uint16_t color = 0;
    color |=  0x001Fu & red;
    color |= (0x03E0u & green) << 5u;
    color |= (0x7C00u & blue) << 10u;

    auto colorIterator = find(d_paletteBytes.begin(), d_paletteBytes.end(), color);
    if(colorIterator != d_paletteBytes.end()) {
        auto index = std::distance(d_paletteBytes.begin(), colorIterator);
        return (uint16_t) index;
    }

    d_paletteBytes.push_back(color);
    return (uint16_t) (d_paletteBytes.size() - 1);
}

void TileSetConverter::parseSheet(const vector<unsigned char> &sheet, unsigned sheetWidth, unsigned sheetHeight,
                                  unsigned tileWidth, unsigned tileHeight) {
    for (int index = 0; index < sheet.size(); index += 4) {
        unsigned char red   = sheet[index];
        unsigned char green = sheet[index + 1];
        unsigned char blue  = sheet[index + 2];
        d_tileBytes.push_back(addColor(red, green, blue));
    }

    d_paletteBytes.resize(PALETTE_COLORS, 0x0000);
}