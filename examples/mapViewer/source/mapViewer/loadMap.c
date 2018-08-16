#include <string.h>
#include "../gbaLib/video/background.h"
#include "../map/map.h"
#include "../gbaLib/gbfs/gbfs.h"
#include "./mapViewer.h"

void loadMap()
{
    const GBFS_FILE *mapFile = find_first_gbfs_file(find_first_gbfs_file);
    u32 mapDataSize = 0;
    const u16 *mapData = gbfs_get_obj(mapFile, MAP_BINARY_NAME, &mapDataSize);

    const u16 *palette = NULL, *tileSet = NULL, *tileMap = NULL;
    u16 sizeFlag = 0, paletteLength = 0, tileSetLength = 0, tileMapLength = 0;

    if (mapData == NULL)
    {
        sizeFlag = mapSizeFlag;

        palette = &mapPalette[0];
        paletteLength = mapPaletteLength;

        tileSet = &mapTileSet[0];
        tileSetLength = mapTileSetLength;

        tileMap = &mapTileMap0[0];
        tileMapLength = mapTileMap0Length;
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

        tileMapLength = mapData[index++];
        tileMap = &mapData[index];
    }

    memcpy(MEMORY_BACKGROUND_PALETTE, palette, paletteLength * 2);
    memcpy(&MEMORY_CHAR_BLOCK[0][0], tileSet, tileSetLength * 2);
    memcpy(&MEMORY_SCREEN_BLOCK[30][0], tileMap, tileMapLength * 2);

    REGISTER_BACKGROUND_CONTROL[0] = FLAG_BACKGROUND_CHAR_BLOCK(0)    |
                                     FLAG_BACKGROUND_SCREEN_BLOCK(30) |
                                     FLAG_BACKGROUND_8BPP             |
                                     sizeFlag;
    REGISTER_DISPLAY_CONTROL = FLAG_MODE0 | FLAG_BACKGROUND0;
}
