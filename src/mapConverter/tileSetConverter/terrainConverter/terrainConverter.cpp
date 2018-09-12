#include "terrainConverter.hpp"
#include "../../../gba/background.h"

TerrainConverter::TerrainConverter(unsigned tileSize) : d_tileSize(tileSize) {
    d_numSubTiles = tileSize / GBA_TILE_SIZE * 2;
}

vector<uint16_t> TerrainConverter::convertTerrainMap(const vector<tmx::Tileset::Tile> &tiles) {
    vector<uint16_t> terrainMapping(tiles.size() * d_numSubTiles, NO_TERRAIN);

    int maxTileID = -1;
    for (tmx::Tileset::Tile tile : tiles) {
        if ((int) tile.ID < maxTileID)
            break;
        maxTileID = tile.ID;

        for (unsigned subTileIndex = 0; subTileIndex < d_numSubTiles; subTileIndex++) {
            int terrainID = chooseTileTerrain(tile.terrainIndices, subTileIndex);
            if (terrainID < 0)
                break;
            terrainMapping[tile.ID * d_numSubTiles + subTileIndex] = (uint16_t) terrainID;
        }
    }

    return terrainMapping;
}

int TerrainConverter::chooseTileTerrain(array<std::int32_t, 4u> terrainIndices, unsigned subTileIndex) {
    float percentage = 1.0f * subTileIndex / d_numSubTiles;
    auto cornerIndex = (unsigned) (percentage * terrainIndices.size());
    return terrainIndices[cornerIndex];
}