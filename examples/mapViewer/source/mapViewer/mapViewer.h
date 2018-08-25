#ifndef MAP_VIEWER_H
#define MAP_VIEWER_H

#include "../gbaLib/video/background.h"

#define MAP_BINARY_NAME "map.bin"
#define MAX_LAYERS 3
#define ENTRIES_IN_SCREEN_BLOCK 512
#define NUM_SCREEN_BLOCKS 31

/**
 * Load the map into memory.
 * @returns The number of layers in the loaded map.
 */
u16 loadMap();

/**
 * Shift a map layer to (offset.x, offset.y).
 * @param layer The map layer to shift.
 * @param offset The offset to shift.
 **/
void shiftMap(u16 layer, BGPoint offset);

#endif // MAP_VIEWER_H
