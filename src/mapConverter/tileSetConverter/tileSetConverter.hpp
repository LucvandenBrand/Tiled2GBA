#ifndef TILE_SET_CONVERTER_H
#define TILE_SET_CONVERTER_H

#include <vector>
#include "../../lib/tmxlite/Tileset.hpp"
#include "image/image.hpp"

using namespace std;

/**
 * Converts Tile Sets to a GBA 256 color palette and GBA Char block.
 */
class TileSetConverter {
public:
    /**
     * Construct the converter.
     * @param tileSet The Tile Set to convert.
     */
    explicit TileSetConverter(const tmx::Tileset &tileSet);

    /**
     * Return the GBA Char block.
     * @return The GBA Char block.
     */
    vector<uint16_t> getTiles();

    /**
     * Return the GBA 256 color palette.
     * @return The 256 color palette.
     */
    vector<uint16_t> getPalette();

private:
    unsigned char remap(unsigned char byte, unsigned char max, unsigned char newMax);
    uint8_t addColor(Color color);
    void parseSheet(Image image, unsigned tileWidth, unsigned tileHeight);

    vector<uint16_t> d_tileBytes;
    vector<uint16_t> d_paletteBytes;
};

#endif // TILE_SET_CONVERTER_H