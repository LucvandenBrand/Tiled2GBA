#include "mapObject.h"
#include "./types.h"

u32 loadObjectID(const u16* idData, u16* index) {
    u32 upperID = popValue(idData, index);
    u32 lowerID = popValue(idData, index);
    return (upperID << 16) | lowerID;
}