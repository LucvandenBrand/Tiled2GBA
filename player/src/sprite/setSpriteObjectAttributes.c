#include "sprite.h"
#include "tonc.h"

void setSpriteObjectAttributes(OBJ_ATTR* spriteObject, u16 attribute0, u16 attribute1, u16 attribute2)
{
    spriteObject->attr0 = attribute0;
    spriteObject->attr1 = attribute1;
    spriteObject->attr2 = attribute2;
}