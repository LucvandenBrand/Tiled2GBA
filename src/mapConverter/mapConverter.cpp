#include "mapConverter.hpp"
#include "tileSetConverter/tileSetConverter.hpp"
#include "tileLayerConverter/tileLayerConverter.hpp"
#include "../log/logger.hpp"
#include <iostream>

GBAMap MapConverter::convert(const string &name, const tmx::Map &tmxMap) {
    auto log = *Logger::getInstance();
    GBAMap gbaMap(name);

    auto tileSize = tmxMap.getTileSize();
    if (tileSize.x != GBA_TILE_SIZE || tileSize.y != GBA_TILE_SIZE) {
        log(ERROR, "The map tile size of "
                           + to_string(tileSize.x) + 'x' + to_string(tileSize.y)
                           + " is not compatible with the GBA."
                           + " The GBA expects 8x8 tiles.");
        exit(EXIT_FAILURE);
    }

    auto tileSets= tmxMap.getTilesets();
    if (tileSets.size() != NUM_TILE_SETS) {
        log(ERROR, "The GBA only supports a single tileSet per map, this map has "
                   + to_string(tileSets.size()) + '.');
        exit(EXIT_FAILURE);
    }

    auto tileSet = tileSets[0];
    auto tileSetConverter = new TileSetConverter(tileSet);
    log(INFO, "Converting tiles.");
    auto tileSetBytes = tileSetConverter->getTiles();
    gbaMap.setTileSet(tileSetBytes);

    log(INFO, "Converting palette.");
    auto paletteBytes = tileSetConverter->getPalette();
    gbaMap.setPalette(paletteBytes);

    const auto& layers = tmxMap.getLayers();
    if (layers.size() > GBA_LAYERS) {
        log(WARN, "This map has " + to_string(layers.size())
                  + ", which is " + to_string(GBA_LAYERS - layers.size())
                  + " more than than the GBA has natively.");
    }

    auto *tileLayerConverter = new TileLayerConverter(tileSet.getFirstGID());
    for (const auto& layer : layers) {
        if (layer->getType() != tmx::Layer::Type::Tile)
            continue;

        log(INFO, "Converting layer '" + layer->getName() + "'.");
        const auto tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());
        auto tileLayerBytes = tileLayerConverter->convert(tileLayer);
        gbaMap.addTileLayer(tileLayerBytes);
    }

    return gbaMap;
}