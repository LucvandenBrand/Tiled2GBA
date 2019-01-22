#include "sprite.h"
#include "../asset/sprite.h"
#include <string.h>

void loadSpriteSheet()
{
    memcpy(MEM_PAL_OBJ, spritePalette, spritePaletteLength * 2);
    memcpy(&tile_mem[4][0], spriteTileSet, spriteTileSetLength * 2);
};