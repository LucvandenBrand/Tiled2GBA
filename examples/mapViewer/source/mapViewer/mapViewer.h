#ifndef MAP_VIEWER_H
#define MAP_VIEWER_H

#include "../gbaLib/video/background.h"
#include "map/map.h"

void shiftMap(Map map, BGPoint offset);
void shiftMapLayer(u16 layer, BGPoint offset);

#endif // MAP_VIEWER_H
