#include <string.h>
#include "../gbaLib/video/background.h"
#include "../map/map.h"
#include "../gbaLib/gbfs/gbfs.h"
#include "./mapViewer.h"

u16 loadMap()
{
    const GBFS_FILE *mapFile = find_first_gbfs_file(find_first_gbfs_file);
    u32 mapDataSize = 0;
    const u16 *mapData = gbfs_get_obj(mapFile, MAP_BINARY_NAME, &mapDataSize);

    const u16 *palette = NULL, *tileSet = NULL, *terrainMap = NULL;
    const u16 *tileMapLayers[3] = {NULL, NULL, NULL};
    u16 sizeFlag = 0, paletteLength = 0, tileSetLength = 0, terrainMapLength = 0, numLayers = 0, tileMapLength = 0;

    if (mapData == NULL)
    {
        sizeFlag = mapSizeFlag;

        paletteLength = mapPaletteLength;
        palette = &mapPalette[0];

        tileSetLength = mapTileSetLength;
        tileSet = &mapTileSet[0];

        numLayers = 1;
        tileMapLength = mapTileMap0Length;
        tileMapLayers[0] = &mapTileMap0[0];
    }
    else
    {
        u32 index = 0;
        sizeFlag = mapData[index++];

        paletteLength = mapData[index++];
        palette = &mapData[index];
        index += paletteLength + 1;

        tileSetLength = mapData[index++];
        tileSet = &mapData[index];
        index += tileSetLength + 1;

        terrainMapLength = mapData[index++];
        terrainMap = &mapData[index];
        index += terrainMapLength;

        numLayers = mapData[index++];
        numLayers = numLayers > MAX_LAYERS ? MAX_LAYERS : numLayers;
        tileMapLength = mapData[index++];
        for (u32 layerIndex = 0; layerIndex < numLayers; ++layerIndex)
        {
            tileMapLayers[layerIndex] = &mapData[index];
            index += tileMapLength;
        }
    }

    memcpy(MEMORY_BACKGROUND_PALETTE, palette, paletteLength * 2);
    memcpy(&MEMORY_CHAR_BLOCK[0][0], tileSet, tileSetLength * 2);

    u32 screenBlockStep = tileMapLength / ENTRIES_IN_SCREEN_BLOCK;
    u32 usedBackgrounds = 0x00;
    for (u32 layerIndex = numLayers; layerIndex-- > 0;)
    {
        u32 screenBlockIndex = NUM_SCREEN_BLOCKS - screenBlockStep * (layerIndex + 1);
        memcpy(&MEMORY_SCREEN_BLOCK[screenBlockIndex][0], tileMapLayers[layerIndex], tileMapLength * 2);

        REGISTER_BACKGROUND_CONTROL[layerIndex] = FLAG_BACKGROUND_CHAR_BLOCK(0)                  |
                                                  FLAG_BACKGROUND_SCREEN_BLOCK(screenBlockIndex) |
                                                  FLAG_BACKGROUND_8BPP                           |
                                                  sizeFlag                                       |
                                                  FLAG_BACKGROUND_PRIORITY(numLayers - layerIndex);
        usedBackgrounds |= FLAG_BACKGROUND(layerIndex);
    }

    REGISTER_DISPLAY_CONTROL = FLAG_MODE0 | usedBackgrounds;

    return numLayers;
}
