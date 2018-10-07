#include "object.h"

u8* loadString(const u16* stringData, u16* index) {
    u16 length = popValue(stringData, index);
    u8* string = (u8*) &stringData[*index];
    *index += length;
    return string;
}