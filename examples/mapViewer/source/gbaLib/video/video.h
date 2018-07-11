#ifndef VIDEO_H
#define VIDEO_H

#include "../memoryMap.h"

/**
 *  Defines general video control.
 */

typedef u16 Color;

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

#define REGISTER_DISPLAY_CONTROL *((vu32*)(REGISTER_BASE+0x0000))

#define FLAG_MODE0 0

#endif // VIDEO_H
