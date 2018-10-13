#include "sprite.h"
#include "../../asset/sprite.h"
#include <string.h>

void loadSpriteSheet()
{
    memcpy(MEMORY_OBJECT_PALETTE, spritePalette, spritePaletteLength * 2);
    memcpy(&MEMORY_CHAR_BLOCK[4][0], spriteTileSet, spriteTileSetLength * 2);
};