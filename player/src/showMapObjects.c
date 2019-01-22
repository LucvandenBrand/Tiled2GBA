#include "main.h"

void showMapObjects(Map* map, OBJ_ATTR* spriteObjects) {
    mapObjectsToSpriteObjects(map->objects, spriteObjects, map->numObjects);
    copySpriteObjectsToMemory(spriteObjects, map->numObjects);
}