#include "mapConverter.hpp"
#include "tileSetConverter/tileSetConverter.hpp"
#include "tileLayerConverter/tileLayerConverter.hpp"
#include "../log/logger.hpp"
#include "../gba/background.h"
#include <iostream>

GBAMap MapConverter::convert(const string &name, const tmx::Map &tmxMap) {
    auto log = *Logger::getInstance();
    GBAMap gbaMap(name);

    auto tileSize = tmxMap.getTileSize();
    if (tileSize.x != tileSize.y) {
        log(ERROR, "Only square map tiles are supported.");
        exit(EXIT_FAILURE);
    }

    if (tileSize.x % GBA_TILE_SIZE != 0) {
        log(ERROR, "The tile size must be a multiple of " + to_string(GBA_TILE_SIZE) + '.');
        exit(EXIT_FAILURE);
    }

    auto mapSize = tmxMap.getTileCount();
    unsigned gbaWidth = mapSize.x * tileSize.x / GBA_TILE_SIZE;
    unsigned gbaHeight = mapSize.y * tileSize.y / GBA_TILE_SIZE;

    auto tileSets= tmxMap.getTilesets();
    if (tileSets.size() != NUM_TILE_SETS) {
        log(ERROR, "The GBA only supports a single tileSet per map, this map has "
                   + to_string(tileSets.size()) + '.');
        exit(EXIT_FAILURE);
    }

    auto tileSet = tileSets[0];
    if (tileSet.getTileSize().x != tileSize.x || tileSet.getTileSize().y != tileSize.y) {
        log(ERROR, "The tileSet must have the same size as the map tiles.");
        exit(EXIT_FAILURE);
    }

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
        auto tileLayerBytes = tileLayerConverter->convert(tileLayer, mapSize.x, mapSize.y, tileSize.x);
        gbaMap.addTileLayer(tileLayerBytes);
    }

    return gbaMap;
}