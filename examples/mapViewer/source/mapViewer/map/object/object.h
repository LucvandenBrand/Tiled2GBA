#ifndef OBJECT_H
#define OBJECT_H

#include "../../../gbaLib/types.h"

typedef struct
{
    u32 id;
    u8 *name;
    u8 *type;
} Object;

Object loadObject(const u16* objectData, u16* index);
u32 loadObjectID(const u16* idData, u16* index);
u8* loadString(const u16* stringData, u16* index);
u16 popValue(const u16* data, u16* index);

#endif