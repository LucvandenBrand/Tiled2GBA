#ifndef MAP_CONVERTER_H
#define MAP_CONVERTER_H

#include "../lib/tmxlite/Map.hpp"
#include "../gba/gbaMap/gbaMap.hpp"
#include "../lib/tmxlite/TileLayer.hpp"

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

private:
    vector<const tmx::TileLayer*> getTileLayers(const vector<tmx::Layer::Ptr> &layers);
    vector<const tmx::ObjectGroup*> getObjectLayers(const vector<tmx::Layer::Ptr> &layers);
};

#endif // MAP_CONVERTER_H