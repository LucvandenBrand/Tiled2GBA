#include "sprite.h"

void initializeSpriteObjectMemory(SpriteObject *spriteObjects, u32 count)
{
    hideSpriteObjects(spriteObjects, count);
    copySpriteObjectsToMemory(spriteObjects, count);
}