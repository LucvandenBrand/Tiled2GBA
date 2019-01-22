#include "mapObject.h"
#include "./types.h"

MapObject loadObject(const u16* objectData, u16* index) {
    MapObject object;
    object.id = loadObjectID(objectData, index);
    object.position = loadPosition(objectData, index);
    object.name = loadString(objectData, index);
    object.type = loadString(objectData, index);
    return object;
}