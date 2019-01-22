#include "mapConverter.hpp"
#include "tileSetConverter/tileSetConverter.hpp"
#include "tileLayerConverter/tileLayerConverter.hpp"
#include "../log/logger.hpp"
#include "../gba/background.h"
#include "objectLayerConverter/objectLayerConverter.hpp"
#include <iostream>

GBAMap MapConverter::convert(const string &name, const tmx::Map &tmxMap) {
    auto log = *Logger::getInstance();

    if (tmxMap.getOrientation() != tmx::Orientation::Orthogonal) {
        log(ERROR, "Only orthogonal maps are supported.");
        exit(EXIT_FAILURE);
    }

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

    if ((gbaWidth  != GBA_MAP_SIZE && gbaWidth  != GBA_MAP_SIZE * 2) ||
        (gbaHeight != GBA_MAP_SIZE && gbaHeight != GBA_MAP_SIZE * 2)) {
        log(ERROR, "The map width and height must be either " + to_string(GBA_MAP_SIZE) +
                   " or " + to_string(GBA_MAP_SIZE * 2) +
                   " tiles large (when subdivided to GBA-sized tiles of "
                   + to_string(GBA_TILE_SIZE) + " pixels large).");
        exit(EXIT_FAILURE);
    };

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

    GBAMap gbaMap(name);

    log(INFO, "Converting size values.");
    gbaMap.setSize(gbaWidth, gbaHeight);

    auto tileSetConverter = new TileSetConverter(tileSet);
    log(INFO, "Converting tiles.");
    auto tileSetBytes = tileSetConverter->getTiles();
    gbaMap.setTileSet(tileSetBytes);

    log(INFO, "Converting palette.");
    auto paletteBytes = tileSetConverter->getPalette();
    gbaMap.setPalette(paletteBytes);

    log(INFO, "Converting terrain.");
    auto terrainMap = tileSetConverter->getTerrainMap();
    gbaMap.setTerrainMap(terrainMap);

    const auto& layers = tmxMap.getLayers();
    const auto tileLayers = getTileLayers(layers);
    if (tileLayers.size() > GBA_LAYERS) {
        log(WARN, "This map has " + to_string(tileLayers.size())
                  + "tile layers, which is " + to_string(tileLayers.size() - GBA_LAYERS)
                  + " more than than the GBA has natively.");
    }

    auto *tileLayerConverter = new TileLayerConverter(tileSet.getFirstGID());
    for (const auto& tileLayer : tileLayers) {
        log(INFO, "Converting tile layer '" + tileLayer->getName() + "'.");
        auto tileLayerBytes = tileLayerConverter->convert(tileLayer, mapSize.x, mapSize.y, tileSize.x);
        gbaMap.addTileLayer(tileLayerBytes);
    }

    const auto objectLayers = getObjectLayers(layers);
    auto *objectLayerConverter = new ObjectLayerConverter();
    for (const auto& objectLayer : objectLayers) {
        log(INFO, "Converting object layer '" + objectLayer->getName() + "'.");
        auto objectLayerBytes = objectLayerConverter->convert(objectLayer);
        gbaMap.addObjects(objectLayerBytes);
    }

    return gbaMap;
}

vector<const tmx::TileLayer*> MapConverter::getTileLayers(const vector<tmx::Layer::Ptr> &layers) {
    vector<const tmx::TileLayer*> tileLayers;

    for (const auto& layer : layers) {
        if (layer->getType() != tmx::Layer::Type::Tile)
            continue;
        const auto tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());
        tileLayers.push_back(tileLayer);
    }

    return tileLayers;
}

vector<const tmx::ObjectGroup*> MapConverter::getObjectLayers(const vector<tmx::Layer::Ptr> &layers) {
    vector<const tmx::ObjectGroup*> objectLayers;

    for (const auto& layer : layers) {
        if (layer->getType() != tmx::Layer::Type::Object)
            continue;
        const auto tileLayer = dynamic_cast<const tmx::ObjectGroup*>(layer.get());
        objectLayers.push_back(tileLayer);
    }

    return objectLayers;
}