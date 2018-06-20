#ifndef TILE_LAYER_CONVERTER_H
#define TILE_LAYER_CONVERTER_H

#include <vector>
#include "../lib/tmxlite/TileLayer.hpp"

using namespace std;

class TileLayerConverter {
public:
    explicit TileLayerConverter(int firstGID);

    vector<uint16_t> convert(const tmx::TileLayer *tileLayer);
private:
    const uint16_t SE_FLIP_H = 0x000A;
    const uint16_t SE_FLIP_V = 0x000B;

    int d_firstGID;
};

#endif // TILE_LAYER_CONVERTER_H