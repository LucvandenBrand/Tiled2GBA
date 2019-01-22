#include "sprite.h"
#include "tonc.h"

void mapObjectsToSpriteObjects(MapObject* mapObjects, OBJ_ATTR* spriteObjects, u32 count)
{
    for (u32 index = 0; index < count; index++)
    {
        u32 tileID = 0;
        u32 paletteBank = 0;
        OBJ_ATTR *spriteObject= &spriteObjects[index];
        setSpriteObjectAttributes(spriteObject,
                                  ATTR0_SQUARE,
                                  ATTR1_SIZE_16,
                                  ATTR2_PALBANK(paletteBank) | tileID);

        ObjectPoint position = mapObjects[index].position;
        setSpriteObjectPosition(spriteObject, position);
    }
}