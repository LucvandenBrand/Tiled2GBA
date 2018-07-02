#include "tileLayerConverter.hpp"
#include "../../gba/background.h"

TileLayerConverter::TileLayerConverter(int firstGID) : d_firstGID(firstGID) {

}

uint16_t TileLayerConverter::convert(unsigned gridID, bool flipH, bool flipV) {
    auto screenEntry = (uint16_t) (gridID - d_firstGID);
    if (flipH)
        screenEntry |= SE_FLIP_H;
    if (flipV)
        screenEntry |= SE_FLIP_V;
    return screenEntry;
}

vector<uint16_t> TileLayerConverter::convert(const tmx::TileLayer *tileLayer, unsigned tileWidth, unsigned tileHeight) {
    unsigned subTilesW = tileWidth / GBA_TILE_SIZE;
    unsigned subTilesH = tileHeight / GBA_TILE_SIZE;
    unsigned numSubTiles = subTilesW * subTilesH;

    vector<uint16_t> bytes;
    const auto& tiles = tileLayer->getTiles();
    bytes.reserve(tiles.size() * numSubTiles);

    for (auto tile : tiles) {
        bool flipH = tile.flipFlags == tmx::TileLayer::FlipFlag::Horizontal;
        bool flipV = tile.flipFlags == tmx::TileLayer::FlipFlag::Vertical;

        for (unsigned subID = 0; subID < numSubTiles; subID++) {
            auto screenEntry = convert(tile.ID * numSubTiles + subID, flipH, flipV);
            bytes.push_back(screenEntry);
        }
    }

    return bytes;
}
