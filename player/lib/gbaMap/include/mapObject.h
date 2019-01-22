#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

typedef struct {
    unsigned short x, y;
} __attribute__((aligned(4))) ObjectPoint;

typedef struct
{
    unsigned int id;
    ObjectPoint position;
    const char* name;
    const char* type;
} MapObject;

MapObject loadObject(const unsigned short* objectData, unsigned short* index);
unsigned int loadObjectID(const unsigned short* idData, unsigned short* index);
ObjectPoint loadPosition(const unsigned short* positionData, unsigned short* index);
const char* loadString(const unsigned short* stringData, unsigned short* index);
unsigned short popValue(const unsigned short* data, unsigned short* index);

void shiftMapObjects(MapObject* objects, ObjectPoint shift, unsigned int count);

#endif