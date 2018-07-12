#ifndef INPUT_H
#define INPUT_H

#define KEY_MASK 0x03FF

#define REGISTER_INPUT_STATE *(vu16*)(REGISTER_BASE+0x0130)

typedef enum KeyIndex
{
	KEY_INDEX_A=0,
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

INLINE KeyState getInputState()
{
    return ~REGISTER_INPUT_STATE & KEY_MASK;
}

INLINE int flagsToTribool(KeyState flags, KeyIndex minus, KeyIndex plus)
{
    return ((flags>>plus)&1) - ((flags>>minus)&1);
}

INLINE int getXAxis(KeyState keyState)
{
    return flagsToTribool(keyState, KEY_INDEX_LEFT, KEY_INDEX_RIGHT);
}

INLINE int getYAxis(KeyState keyState)
{
    return flagsToTribool(keyState, KEY_INDEX_UP, KEY_INDEX_DOWN);
}

#endif // INPUT_H
