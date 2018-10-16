#include "main.h"

void showMapObjects(Map* map, SpriteObject* spriteObjects) {
    mapObjectsToSpriteObjects(map->objects, spriteObjects, map->numObjects);
    copySpriteObjectsToMemory(spriteObjects, map->numObjects);
}