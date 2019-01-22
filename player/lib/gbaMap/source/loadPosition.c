#include "mapObject.h"
#include "./types.h"

ObjectPoint loadPosition(const u16* positionData, u16* index) {
    ObjectPoint position;
    position.x = popValue(positionData, index);
    position.y = popValue(positionData, index);
    return position;
}