#ifndef TILE_SET_CONVERTER_H
#define TILE_SET_CONVERTER_H

#include <vector>
#include "../../lib/tmxlite/Tileset.hpp"

using namespace std;

class TileSetConverter {
public:
    explicit TileSetConverter(const tmx::Tileset &tileSet);

    vector<uint16_t> getTiles();
    vector<uint16_t> getPalette();

private:
    void parseSheet(const vector<unsigned char> &sheet, unsigned sheetWidth, unsigned sheetHeight,
                    unsigned tileWidth, unsigned tileHeight);
    uint8_t addColor(unsigned char red, unsigned char green, unsigned char blue);
    unsigned char remap(unsigned char byte, unsigned char max, unsigned char newMax);

    const uint16_t GBA_TILE_SIZE = 8;
    unsigned int PALETTE_COLORS = 256;

    vector<uint16_t> d_tileBytes;
    vector<uint16_t> d_paletteBytes;
};

#endif // TILE_SET_CONVERTER_H