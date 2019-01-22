#ifndef MAP_H
#define MAP_H

#include "mapObject.h"

typedef struct {
    unsigned short sizeFlag,
        paletteLength,
        tileSetLength,
        terrainMapLength,
        numObjects,
        numLayers,
        tileMapLength;

    const unsigned short *palette,
              *tileSet,
              *terrainMap;

    MapObject objects[256];

    const unsigned short *tileMapLayers[3];
} Map;

typedef struct {
    short x, y;
} __attribute__((aligned(4))) BackgroundPoint;

#define MAX_LAYERS 3
#define ENTRIES_IN_SCREEN_BLOCK 512
#define NUM_SCREEN_BLOCKS 31

Map loadMapFromROM(const unsigned short *mapData);

void setMapOnScreen(Map map);
void shiftMap(Map map, BackgroundPoint offset);
void shiftMapLayer(unsigned short layer, BackgroundPoint offset);

#endif
