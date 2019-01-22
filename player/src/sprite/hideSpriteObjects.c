#include "sprite.h"
#include "tonc.h"

void hideSpriteObjects(OBJ_ATTR *spriteObjects, u32 count)
{
    u32* wordPointer = (u32*) spriteObjects;
    for (u32 index = 0; index < count; index++)
    {
        *wordPointer++ = ATTR0_HIDE;
        *wordPointer++ = 0;
    }
}