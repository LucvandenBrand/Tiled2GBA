#ifndef MAP_CONVERTER_H
#define MAP_CONVERTER_H

#include "../lib/tmxlite/Map.hpp"
#include "../gba/gbaMap/gbaMap.hpp"

using namespace std;

/**
 * Converts a TMX Map to a GBA Map.
 */
class MapConverter {
public:
    /**
     * Convert a TMX Map.
     * @param tmxMap The TMX Map.
     * @return The GBA Map.
     */
    GBAMap convert(const string &name, const tmx::Map &tmxMap);
};

#endif // MAP_CONVERTER_H