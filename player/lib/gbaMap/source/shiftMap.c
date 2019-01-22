#include "map.h"
#include "./background.h"

void shiftMap(Map map, BackgroundPoint offset)
{
    for (u16 layer = 0; layer < map.numLayers; layer++)
        shiftMapLayer(layer, offset);
}
