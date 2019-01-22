#include "./main.h"
#include <string.h>
#include "gbfs.h"

Map loadMap()
{
    u32 mapDataSize = 0;
    const GBFS_FILE *mapFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16 *mapData = gbfs_get_obj(mapFile, "map.bin", &mapDataSize);

    if (mapData == NULL)
        return loadMapFromCode();

    return loadMapFromROM(mapData);
}
