#ifndef TILE_LAYER_CONVERTER_H
#define TILE_LAYER_CONVERTER_H

#include <vector>
#include "../../lib/tmxlite/TileLayer.hpp"

using namespace std;

/**
 * Converts a Tile Layer to GBA screen block bytes.
 */
class TileLayerConverter {
public:
    /**
     * Construct the converter.
     * @param firstGID The first ID of the tile set.
     */
    explicit TileLayerConverter(int firstGID);

    /**
     * Convert a Tile Layer.
     * @param tileLayer The Tile Layer.
     * @return A vector of bytes representing 16 bit screen block entries.
     */
    vector<uint16_t> convert(const tmx::TileLayer *tileLayer, unsigned width, unsigned height, unsigned tileSize);
private:
    const uint16_t SE_FLIP_H = 0x000A;
    const uint16_t SE_FLIP_V = 0x000B;

    int d_firstGID;

    uint16_t convert(unsigned gridID, bool flipH, bool flipV);

    unsigned coordToIndex(unsigned row, unsigned col, unsigned width);
};

#endif // TILE_LAYER_CONVERTER_H