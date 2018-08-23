#ifndef MAP_VIEWER_H
#define MAP_VIEWER_H

#include "../gbaLib/video/background.h"

#define MAP_BINARY_NAME "map.bin"
#define MAX_LAYERS 3
#define ENTRIES_IN_SCREEN_BLOCK 512
#define NUM_SCREEN_BLOCKS 31

/**
 * Load the map into memory.
 */
void loadMap();

/**
 * Shift the map to (offset.x, offset.y).
 **/
void shiftMap(BGPoint offset);

#endif // MAP_VIEWER_H
