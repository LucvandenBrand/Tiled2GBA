#include "object.h"

Object loadObject(const u16* objectData, u16* index) {
    Object object;
    object.id = loadObjectID(objectData, index);
    object.position = loadPosition(objectData, index);
    object.name = loadString(objectData, index);
    object.type = loadString(objectData, index);
    return object;
}