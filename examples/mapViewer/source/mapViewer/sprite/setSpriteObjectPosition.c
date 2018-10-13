#include "sprite.h"
#include "../../gbaLib/bitField.h"

void setSpriteObjectPosition(SpriteObject* spriteObject, ObjectPoint position)
{
    BIT_FIELD_SET(spriteObject->attribute0, position.y, ATTRIBUTE0_Y);
    BIT_FIELD_SET(spriteObject->attribute1, position.x, ATTRIBUTE1_X);
}