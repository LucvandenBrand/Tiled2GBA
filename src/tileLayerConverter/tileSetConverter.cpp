#include "tileLayerConverter.h"

TileLayerConverter::TileLayerConverter(int firstGID) : d_firstGID(firstGID) {

}

vector<uint16_t> TileLayerConverter::convert(const tmx::TileLayer *tileLayer) {
    vector<uint16_t> bytes;
    const auto& tiles = tileLayer->getTiles();
    bytes.reserve(tiles.size());

    for (auto tile : tiles) {
        auto screenEntry = (uint16_t) (tile.ID - d_firstGID);
        if (tile.flipFlags == tmx::TileLayer::FlipFlag::Horizontal)
            screenEntry |= SE_FLIP_H;
        if (tile.flipFlags == tmx::TileLayer::FlipFlag::Vertical)
            screenEntry |= SE_FLIP_V;

        bytes.push_back(screenEntry);
    }

    return bytes;
}
