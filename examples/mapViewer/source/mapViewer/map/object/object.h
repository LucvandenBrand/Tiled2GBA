#ifndef OBJECT_H
#define OBJECT_H

#include "../../../gbaLib/types.h"

typedef struct {
    u16 x, y;
} ALIGN(4) ObjectPoint;

typedef struct
{
    u32 id;
    ObjectPoint position;
    const char* name;
    const char* type;
} Object;

Object loadObject(const u16* objectData, u16* index);
u32 loadObjectID(const u16* idData, u16* index);
ObjectPoint loadPosition(const u16* positionData, u16* index);
const char* loadString(const u16* stringData, u16* index);
u16 popValue(const u16* data, u16* index);

void shiftMapObjects(Object* objects, ObjectPoint shift, u32 count);

#endif