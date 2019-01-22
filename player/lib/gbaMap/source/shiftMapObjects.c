#include "mapObject.h"
#include "./types.h"

void shiftMapObjects(MapObject* objects, ObjectPoint shift, u32 count)
{
    for (u32 index = 0; index < count; index++)
    {
        objects[index].position.x -= shift.x;
        objects[index].position.y -= shift.y;
    }
}