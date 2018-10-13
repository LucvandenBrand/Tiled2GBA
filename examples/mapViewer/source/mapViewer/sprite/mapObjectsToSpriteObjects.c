#include "sprite.h"

void mapObjectsToSpriteObjects(Object* mapObjects, SpriteObject* spriteObjects, u32 count)
{
    for (u32 index = 0; index < count; index++)
    {
        u32 tileID = 0;
        u32 paletteBank = 0;
        SpriteObject *spriteObject= &spriteObjects[index];
        setSpriteObjectAttributes(spriteObject,
                                  ATTRIBUTE0_SQUARE,
                                  ATTRIBUTE1_SIZE_16,
                                  ATTRIBUTE2_PALETTE_BANK(paletteBank) | tileID);

        ObjectPoint position = mapObjects[index].position;
        setSpriteObjectPosition(spriteObject, position);
    }
}