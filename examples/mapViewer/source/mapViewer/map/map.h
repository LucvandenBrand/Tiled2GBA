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

#endif
