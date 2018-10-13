#ifndef SPRITE_H
#define SPRITE_H

#include "../../gbaLib/video/object.h"
#include "../map/object/object.h"

void loadSpriteSheet();
void initializeSpriteObjectMemory(SpriteObject *spriteObjects, u32 count);
void hideSpriteObjects(SpriteObject *spriteObjects, u32 count);
void copySpriteObjectsToMemory(const SpriteObject *spriteObjects, u32 count);
void setSpritesOnScreen();
void mapObjectsToSpriteObjects(Object* mapObjects, SpriteObject* spriteObjects, u32 count);
void setSpriteObjectAttributes(SpriteObject* spriteObject, u16 attribute0, u16 attribute1, u16 attribute2);
void setSpriteObjectPosition(SpriteObject* spriteObject, ObjectPoint position);

#endif