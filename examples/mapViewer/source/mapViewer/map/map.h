#ifndef MAP_H
#define MAP_H

#include "../../gbaLib/types.h"

typedef struct {
    u16 sizeFlag,
        paletteLength,
        tileSetLength,
        terrainMapLength,
        numLayers,
        tileMapLength;

    const u16 *palette,
              *tileSet,
              *terrainMap;

    const u16 *tileMapLayers[3];
} Map;

#define MAP_BINARY_NAME "map.bin"
#define MAX_LAYERS 3
#define ENTRIES_IN_SCREEN_BLOCK 512
#define NUM_SCREEN_BLOCKS 31

Map loadMap();
Map loadMapFromROM(const u16 *mapData);
Map loadMapFromCode();

void setMapOnScreen(Map map);

#endif
