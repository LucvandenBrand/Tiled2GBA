#include "tileLayerConverter.hpp"
#include "../../gba/background.h"

TileLayerConverter::TileLayerConverter(int firstGID) : d_firstGID(firstGID) {

}

unsigned TileLayerConverter::coordToIndex(unsigned row, unsigned col, unsigned width) {
    return row * width + col;
}

uint16_t TileLayerConverter::convert(unsigned gridID, bool flipH, bool flipV) {
    auto screenEntry = (uint16_t) gridID;
    if (flipH)
        screenEntry |= SE_FLIP_H;
    if (flipV)
        screenEntry |= SE_FLIP_V;
    return screenEntry;
}

vector<uint16_t> TileLayerConverter::convert(const tmx::TileLayer *tileLayer, unsigned width, unsigned height, unsigned tileSize) {
    unsigned subTiles = tileSize / GBA_TILE_SIZE;
    unsigned screenWidth = width * subTiles;
    unsigned screenHeight = height * subTiles;
    vector<uint16_t> bytes(screenWidth * screenHeight, 0);
    const auto& tiles = tileLayer->getTiles();

    for (unsigned row = 0; row < height; row++) {
        for (unsigned col = 0; col < width; col++) {
            auto tile = tiles[coordToIndex(row, col, width)];
            bool flipH = tile.flipFlags == tmx::TileLayer::FlipFlag::Horizontal;
            bool flipV = tile.flipFlags == tmx::TileLayer::FlipFlag::Vertical;
            unsigned baseID = (tile.ID - d_firstGID) * subTiles * subTiles;

            for (unsigned subRow = 0; subRow < subTiles; subRow++) {
                for (unsigned subCol = 0; subCol < subTiles; subCol++) {
                    uint16_t screenEntry = convert(baseID + subRow * subTiles + subCol, flipH, flipV);
                    unsigned screenRow = row * subTiles + subRow;
                    unsigned screenCol = col * subTiles + subCol;
                    bytes[coordToIndex(screenRow, screenCol, screenWidth)] = screenEntry;
                }
            }
        }
    }

    return bytes;
}
