#include "../gbaLib/video/background.h"

void shiftMap(u16 layer, BGPoint offset)
{
    REGISTER_BACKGROUND_OFFSET[layer] = offset;
}
