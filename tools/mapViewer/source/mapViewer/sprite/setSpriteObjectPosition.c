#include "sprite.h"
#include "../../gbaLib/bitField.h"

void setSpriteObjectPosition(SpriteObject* spriteObject, ObjectPoint position)
{
    BIT_FIELD_SET(spriteObject->attribute0, position.y - 8, ATTRIBUTE0_Y);
    BIT_FIELD_SET(spriteObject->attribute1, position.x - 8, ATTRIBUTE1_X);
}