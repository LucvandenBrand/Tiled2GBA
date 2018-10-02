#ifndef TILE_SET_CONVERTER_H
#define TILE_SET_CONVERTER_H

#include <vector>
#include "../../lib/tmxlite/Tileset.hpp"
#include "image/image.hpp"

using namespace std;

/**
 * Converts Tile Sets to a GBA 256 color palette, a GBA Char block and terrain data.
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

    /**
     * Return the tile-terrain mapping
     * @return The tile-terrain mapping.
     */
    vector<uint16_t> getTerrainMap();

private:
    Color tmxColourToColor(tmx::Colour colour);
    uint8_t remap(uint8_t byte, uint8_t max, uint8_t newMax);
    uint8_t addColor(Color color);
    void parseSheet(Image image, unsigned tileSize);
    void generateColorTile(const Color &color);
    uint16_t combinePixels(uint8_t firstPixel, uint8_t secondPixel);

    vector<uint16_t> d_tileBytes;
    vector<uint16_t> d_paletteBytes;
    vector<uint16_t> d_terrainMapBytes;
};

#endif // TILE_SET_CONVERTER_H