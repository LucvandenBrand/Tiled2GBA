#include "./background.h"
#include "map.h"

void shiftMapLayer(u16 layer, BackgroundPoint offset)
{
    REGISTER_BACKGROUND_OFFSET[layer] = offset;
}
