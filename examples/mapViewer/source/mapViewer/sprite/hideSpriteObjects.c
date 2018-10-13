#include "sprite.h"

void hideSpriteObjects(SpriteObject *spriteObjects, u32 count)
{
    u32* wordPointer = (u32*) spriteObjects;
    for (u32 index = 0; index < count; index++)
    {
        *wordPointer++ = ATTRIBUTE0_HIDE;
        *wordPointer++ = 0;
    }
}