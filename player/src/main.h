#ifndef MAIN_H
#define MAIN_H

#include "map.h"
#include "./sprite/sprite.h"

void showMapObjects(Map* map, OBJ_ATTR* spriteObjects);
Map loadMapFromCode();
Map loadMap();

#endif