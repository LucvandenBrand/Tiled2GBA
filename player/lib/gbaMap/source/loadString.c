#include "mapObject.h"
#include "./types.h"

const char* loadString(const u16* stringData, u16* index) {
    u16 length = popValue(stringData, index);
    const char* string = (const char*) &stringData[*index];
    *index += length;
    return string;
}