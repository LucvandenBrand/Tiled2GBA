#ifndef SPRITE_H
#define SPRITE_H

#include "mapObject.h"
#include "tonc.h"

void loadSpriteSheet();
void initializeSpriteObjectMemory(OBJ_ATTR *spriteObjects, u32 count);
void hideSpriteObjects(OBJ_ATTR *spriteObjects, u32 count);
void copySpriteObjectsToMemory(const OBJ_ATTR *spriteObjects, u32 count);
void setSpritesOnScreen();
void mapObjectsToSpriteObjects(MapObject* mapObjects, OBJ_ATTR* spriteObjects, u32 count);
void setSpriteObjectAttributes(OBJ_ATTR* spriteObject, u16 attribute0, u16 attribute1, u16 attribute2);
void setSpriteObjectPosition(OBJ_ATTR* spriteObject, ObjectPoint position);

#endif