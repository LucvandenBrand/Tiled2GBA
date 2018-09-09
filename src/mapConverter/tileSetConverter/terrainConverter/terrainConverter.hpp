#ifndef TERRAIN_CONVERTER_H
#define TERRAIN_CONVERTER_H

#include <cstdint>
#include <vector>
#include "../../../lib/tmxlite/Tileset.hpp"

using namespace std;

/**
 * Converts tile terrain data into more simple gba terrain data.
 */
class TerrainConverter {
public:
    /**
     * Construct and instance of the terrain converter.
     * @param tileSize The size of a single tile.
     */
    explicit TerrainConverter(unsigned tileSize);

    /**
     * Convert a list of tiles into a mapping between tile id's and terrain indices.
     * @param tiles The tiles in a tile set
     * @return Integer vector describing the tile-terrain mapping.
     */
    vector<uint16_t> convertTerrainMap(const vector<tmx::Tileset::Tile> &tiles);

private:
    int chooseTileTerrain(array<std::int32_t, 4u> terrainIndices, unsigned subTileIndex);

    const uint16_t NO_TERRAIN = UINT16_MAX;
    unsigned d_tileSize, d_numSubTiles;
};

#endif