#ifndef INPUT_H
#define INPUT_H

#include "tonc.h"

/**
 * Defines user input access.
 **/

#define KEY_MASK 0x03FF

typedef enum KeyIndex
{
	KEY_INDEX_A = 0,
    KEY_INDEX_B,
    KEY_INDEX_SELECT,
    KEY_INDEX_START,
	KEY_INDEX_RIGHT,
    KEY_INDEX_LEFT,
    KEY_INDEX_UP,
    KEY_INDEX_DOWN,
	KEY_INDEX_R_TRIGGER,
    KEY_INDEX_L_TRIGGER,
    KEY_INDEX_MAX
} KeyIndex;

typedef u16 KeyState;

/**
 * Get the current state of all keys.
 **/
INLINE KeyState getInputState()
{
    return ~REG_KEYINPUT & KEY_MASK;
}

/**
 * Convert two keys into a range of (-1, 1).
 **/
INLINE int flagsToTribool(KeyState flags, KeyIndex minus, KeyIndex plus)
{
    return ((flags>>plus)&1) - ((flags>>minus)&1);
}

/**
 * Get the X-axis value of the arrow pad.
 * -1 is for left, +1 is for right.
 **/
INLINE int getXAxis(KeyState keyState)
{
    return flagsToTribool(keyState, KEY_INDEX_LEFT, KEY_INDEX_RIGHT);
}

/**
 * Get the Y-axis value of the arrow pad.
 * -1 is for up, +1 is for down.
 **/
INLINE int getYAxis(KeyState keyState)
{
    return flagsToTribool(keyState, KEY_INDEX_UP, KEY_INDEX_DOWN);
}

#endif // INPUT_H
