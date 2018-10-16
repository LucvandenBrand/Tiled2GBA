#include "sprite.h"

void copySpriteObjectsToMemory(const SpriteObject *spriteObjects, u32 count)
{
    u32* destinationWordPointer = (u32*) MEMORY_SPRITE_OBJECTS;
    u32* sourceWordPointer = (u32*) spriteObjects;
    for (u32 index = 0; index < count; index++)
    {
        *destinationWordPointer++ = *sourceWordPointer++;
        *destinationWordPointer++ = *sourceWordPointer++;
    }
}