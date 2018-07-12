#include "../gbaLib/video/background.h"

void shiftMap(BGPoint offset)
{
    REGISTER_BACKGROUND_OFFSET[0] = offset;
}
