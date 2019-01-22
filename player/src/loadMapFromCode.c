#include "map.h"
#include "mapObject.h"
#include "tonc.h"
#include "asset/map.h"

Map loadMapFromCode() {
    Map map;

    map.sizeFlag = mapSizeFlag;

    map.paletteLength = mapPaletteLength;
    map.palette = &mapPalette[0];

    map.tileSetLength = mapTileSetLength;
    map.tileSet = &mapTileSet[0];

    map.numLayers = 1;
    map.tileMapLength = mapTileMap0Length;
    map.tileMapLayers[0] = &mapTileMap0[0];

    u16 objectDataIndex = 0;
    u32 objectCount = 0;
    while (objectDataIndex != mapObjectsLength) {
        MapObject object = loadObject(mapObjects, &objectDataIndex);
        map.objects[objectCount] = object;
        objectCount++;
    }
    map.numObjects = objectCount;

    return map;
}
