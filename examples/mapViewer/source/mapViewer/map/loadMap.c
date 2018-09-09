#include <string.h>
#include "../../gbaLib/video/background.h"
#include "./map.h"
#include "../../gbaLib/gbfs/gbfs.h"
#include "../mapViewer.h"

Map loadMap()
{
    u32 mapDataSize = 0;
    const GBFS_FILE *mapFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16 *mapData = gbfs_get_obj(mapFile, MAP_BINARY_NAME, &mapDataSize);

    if (mapData == NULL)
        return loadMapFromCode();
        
    return loadMapFromROM(mapData);
}
