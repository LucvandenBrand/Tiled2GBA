#ifndef MAP_CONVERTER_H
#define MAP_CONVERTER_H

#include "../lib/tmxlite/Map.hpp"
#include "../gbaMap/gbaMap.hpp"

using namespace std;

class MapConverter {
public:
    GBAMap convert(const tmx::Map &tmxMap);
private:
    const int GBA_LAYERS = 3;
    const int TILE_SIZE = 8;
    const int NUM_TILE_SETS = 1;
};

#endif // MAP_CONVERTER_H