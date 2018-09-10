#include "../gbaLib/video/background.h"

void shiftMapLayer(u16 layer, BGPoint offset)
{
    REGISTER_BACKGROUND_OFFSET[layer] = offset;
}
