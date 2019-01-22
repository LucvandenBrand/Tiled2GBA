#include "sprite.h"
#include "tonc.h"

void copySpriteObjectsToMemory(const OBJ_ATTR *spriteObjects, u32 count)
{
    u32* destinationWordPointer = (u32*) oam_mem;
    u32* sourceWordPointer = (u32*) spriteObjects;
    for (u32 index = 0; index < count; index++)
    {
        *destinationWordPointer++ = *sourceWordPointer++;
        *destinationWordPointer++ = *sourceWordPointer++;
    }
}