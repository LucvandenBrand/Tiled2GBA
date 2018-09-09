#include "map.h"
#include "../mapViewer.h"

Map loadMapFromROM(const u16 *mapData) {
    Map map;
    u32 index = 0;

    map.sizeFlag = mapData[index++];

    map.paletteLength = mapData[index++];
    map.palette = &mapData[index];
    index += map.paletteLength + 1;

    map.tileSetLength = mapData[index++];
    map.tileSet = &mapData[index];
    index += map.tileSetLength + 1;

    map.terrainMapLength = mapData[index++];
    map.terrainMap = &mapData[index];
    index += map.terrainMapLength;

    map.numLayers = mapData[index++];
    map.numLayers = map.numLayers > MAX_LAYERS ? MAX_LAYERS : map.numLayers;
    map.tileMapLength = mapData[index++];
    for (u32 layerIndex = 0; layerIndex < map.numLayers; ++layerIndex)
    {
        map.tileMapLayers[layerIndex] = &mapData[index];
        index += map.tileMapLength;
    }

    return map;
}
