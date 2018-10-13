#include "sprite.h"

void setSpriteObjectAttributes(SpriteObject* spriteObject, u16 attribute0, u16 attribute1, u16 attribute2)
{
    spriteObject->attribute0 = attribute0;
    spriteObject->attribute1 = attribute1;
    spriteObject->attribute2 = attribute2;
}