#include <string.h>
#include "../../gbaLib/video/background.h"
#include "./map.h"
#include "../../gbaLib/gbfs/gbfs.h"
#include "../mapViewer.h"

u16 loadMap()
{
    u32 mapDataSize = 0;
    const GBFS_FILE *mapFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16 *mapData = gbfs_get_obj(mapFile, MAP_BINARY_NAME, &mapDataSize);
    Map map;

    if (mapData == NULL)
        map = loadMapFromCode();
    else
        map = loadMapFromROM(mapData);

    memcpy(MEMORY_BACKGROUND_PALETTE, map.palette, map.paletteLength * 2);
    memcpy(&MEMORY_CHAR_BLOCK[0][0], map.tileSet, map.tileSetLength * 2);

    u32 screenBlockStep = map.tileMapLength / ENTRIES_IN_SCREEN_BLOCK;
    u32 usedBackgrounds = 0x00;
    for (u32 layerIndex = map.numLayers; layerIndex-- > 0;)
    {
        u32 screenBlockIndex = NUM_SCREEN_BLOCKS - screenBlockStep * (layerIndex + 1);
        memcpy(&MEMORY_SCREEN_BLOCK[screenBlockIndex][0], map.tileMapLayers[layerIndex], map.tileMapLength * 2);

        REGISTER_BACKGROUND_CONTROL[layerIndex] = FLAG_BACKGROUND_CHAR_BLOCK(0)                  |
                                                  FLAG_BACKGROUND_SCREEN_BLOCK(screenBlockIndex) |
                                                  FLAG_BACKGROUND_8BPP                           |
                                                  map.sizeFlag                                   |
                                                  FLAG_BACKGROUND_PRIORITY(map.numLayers - layerIndex);
        usedBackgrounds |= FLAG_BACKGROUND(layerIndex);
    }

    REGISTER_DISPLAY_CONTROL = FLAG_MODE0 | usedBackgrounds;

    return map.numLayers;
}
