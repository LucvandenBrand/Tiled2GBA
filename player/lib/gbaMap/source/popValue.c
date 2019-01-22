#include "mapObject.h"
#include "./types.h"

u16 popValue(const u16* data, u16* index) {
    u16 value = data[*index];
    *index += 1;
    return value;
}