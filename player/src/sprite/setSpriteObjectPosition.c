#include "sprite.h"
#include "tonc.h"

void setSpriteObjectPosition(OBJ_ATTR* spriteObject, ObjectPoint position)
{
    BFN_SET(spriteObject->attr0, position.y - 8, ATTR0_Y);
    BFN_SET(spriteObject->attr1, position.x - 8, ATTR1_X);
}