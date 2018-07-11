#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include "types.h"

/**
 *  Defines the memory locations.
 */

#define MEMORY_IO       0x04000000
#define MEMORY_PALETTE  0x05000000
#define MEMORY_VIDEORAM 0x06000000

#define REGISTER_BASE MEMORY_IO

#endif // MEMORY_MAP_H
