#include "sprite.h"

void setSpritesOnScreen()
{
    REGISTER_DISPLAY_CONTROL |= FLAG_SPRITE_OBJECTS | FLAG_1D_SPRITE_SHEET;
}