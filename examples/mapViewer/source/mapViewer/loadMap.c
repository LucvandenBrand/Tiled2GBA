#include <string.h>
#include "../gbaLib/video/background.h"
#include "../map/map.h"

void loadMap()
{
    memcpy(MEMORY_BACKGROUND_PALETTE, mapPalette, mapPaletteLength);
    memcpy(&MEMORY_CHAR_BLOCK[0][0], mapTileSet, mapTileSetLength);
    memcpy(&MEMORY_SCREEN_BLOCK[30][0], mapTileMap0, mapTileMap0Length);

    REGISTER_BACKGROUND_CONTROL[0] = FLAG_BACKGROUND_CHAR_BLOCK(0)    |
                                     FLAG_BACKGROUND_SCREEN_BLOCK(30) |
                                     FLAG_BACKGROUND_8BPP             |
                                     FLAG_BACKGROUND_REGULAR_32x64;
    REGISTER_DISPLAY_CONTROL = FLAG_MODE0 | FLAG_BACKGROUND0;
}
