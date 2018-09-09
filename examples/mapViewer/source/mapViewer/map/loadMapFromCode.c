#include "map.h"
#include "../../map/map.h"
#include "../mapViewer.h"

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

    return map;
}
