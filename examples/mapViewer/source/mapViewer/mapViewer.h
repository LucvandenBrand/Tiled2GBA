#ifndef MAP_VIEWER_H
#define MAP_VIEWER_H

#include "../gbaLib/video/background.h"

/**
 * Load the map into memory.
 */
void loadMap();

/**
 * Shift the map to (offset.x, offset.y).
 **/
void shiftMap(BGPoint offset);

#endif // MAP_VIEWER_H
