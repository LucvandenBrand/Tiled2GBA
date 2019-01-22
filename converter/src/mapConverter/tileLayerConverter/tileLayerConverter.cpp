#include "tileLayerConverter.hpp"
#include "../../gba/background.h"

TileLayerConverter::TileLayerConverter(int firstGID) : d_firstGID(firstGID) {}

unsigned TileLayerConverter::coordToIndex(unsigned row, unsigned col, unsigned width) {
    return row * width + col;
}

vector<tmx::TileLayer::Tile>
TileLayerConverter::selectCrop(const vector<tmx::TileLayer::Tile> &tiles, unsigned cropRow, unsigned cropCol, unsigned mapWidth,
                               unsigned size) {
    vector<tmx::TileLayer::Tile> cropTiles(size * size);
    for (unsigned row = 0; row < size; row++)
        for (unsigned col = 0; col < size; col++)
            cropTiles[coordToIndex(row, col, size)] = tiles[coordToIndex(cropRow + row, cropCol + col, mapWidth)];

    return cropTiles;
}

uint16_t TileLayerConverter::convert(unsigned gridID, bool flipH, bool flipV) {
    auto screenEntry = (uint16_t) gridID;
    if (flipH)
        screenEntry |= SE_FLIP_H;
    if (flipV)
        screenEntry |= SE_FLIP_V;
    return screenEntry;
}

vector<uint16_t> TileLayerConverter::convertCrop(const vector<tmx::TileLayer::Tile> &tiles,
                                                 unsigned size, unsigned subTiles) {
    vector<uint16_t> cropBytes(size * size * subTiles * subTiles, 0);

    for (unsigned row = 0; row < size; row++) {
        for (unsigned col = 0; col < size; col++) {
            auto tile = tiles[coordToIndex(row, col, size)];
            bool flipH = tile.flipFlags == tmx::TileLayer::FlipFlag::Horizontal;
            bool flipV = tile.flipFlags == tmx::TileLayer::FlipFlag::Vertical;

            unsigned baseID = (tile.ID - d_firstGID) * subTiles * subTiles;
            bool isEmpty = baseID < 0;

            for (unsigned subRow = 0; subRow < subTiles; subRow++) {
                for (unsigned subCol = 0; subCol < subTiles; subCol++) {
                    unsigned subTileID = 0;
                    if (!isEmpty)
                        subTileID = baseID + subRow * subTiles + subCol + 1;

                    uint16_t screenEntry = convert(subTileID, flipH, flipV);
                    unsigned screenRow = row * subTiles + subRow;
                    unsigned screenCol = col * subTiles + subCol;
                    cropBytes[coordToIndex(screenRow, screenCol, size * subTiles)] = screenEntry;
                }
            }
        }
    }

    return cropBytes;
}

vector<uint16_t> TileLayerConverter::convert(const tmx::TileLayer *tileLayer, unsigned width, unsigned height, unsigned tileSize) {
    vector<uint16_t> bytes;
    const vector<tmx::TileLayer::Tile> &tiles = tileLayer->getTiles();

    unsigned subTiles = tileSize / GBA_TILE_SIZE;
    unsigned screenBlockSize = GBA_MAP_SIZE / subTiles;

    for (unsigned row = 0; row < height; row += screenBlockSize) {
        for (unsigned col = 0; col < width; col += screenBlockSize) {
            vector<tmx::TileLayer::Tile> cropTiles = selectCrop(tiles, row, col, width, screenBlockSize);
            vector<uint16_t> cropBytes = convertCrop(cropTiles, screenBlockSize, subTiles);
            bytes.insert(bytes.end(), cropBytes.begin(), cropBytes.end());
        }
    }

    return bytes;
}
