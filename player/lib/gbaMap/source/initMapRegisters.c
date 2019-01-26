#include "map.h"
#include "./background.h"

void initMapRegisters() {
    for (u32 layerIndex = MAX_LAYERS; layerIndex-- > 0;) {
        REGISTER_BACKGROUND_CONTROL[layerIndex] = 0;
    }

    REGISTER_DISPLAY_CONTROL = 0;
}