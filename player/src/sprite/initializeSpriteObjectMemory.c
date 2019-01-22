#include "sprite.h"
#include "tonc.h"

void initializeSpriteObjectMemory(OBJ_ATTR *spriteObjects, u32 count)
{
    hideSpriteObjects(spriteObjects, count);
    copySpriteObjectsToMemory(spriteObjects, count);
}