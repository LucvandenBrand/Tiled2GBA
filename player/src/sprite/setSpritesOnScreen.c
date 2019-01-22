#include "sprite.h"

void setSpritesOnScreen()
{
    REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;
}