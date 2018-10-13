#ifndef MAP_H
#define MAP_H

#include "../../gbaLib/types.h"
#include "../../gbaLib/video/background.h"
#include "mapObject/mapObject.h"

typedef struct {
    u16 sizeFlag,
        paletteLength,
        tileSetLength,
        terrainMapLength,
        numObjects,
        numLayers,
        tileMapLength;

    const u16 *palette,
              *tileSet,
              *terrainMap;

    MapObject objects[256];

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
void shiftMap(Map map, BackgroundPoint offset);
void shiftMapLayer(u16 layer, BackgroundPoint offset);

#endif
