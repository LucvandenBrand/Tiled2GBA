#include "mapConverter.hpp"
#include "tileSetConverter/tileSetConverter.hpp"
#include "tileLayerConverter/tileLayerConverter.hpp"
#include <iostream>

GBAMap MapConverter::convert(const tmx::Map &tmxMap) {
    auto tileSize = tmxMap.getTileSize();
    if (tileSize.x != TILE_SIZE || tileSize.y != TILE_SIZE) {
        cout << "[ERR] The tile size of " << tileSize.x << 'x' << tileSize.y << " is not compatible with the GBA." << endl;
        cout << "The GBA expects 8x8 tiles." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Converting tileSet:" << endl;
    auto tileSets= tmxMap.getTilesets();
    if (tileSets.size() != NUM_TILE_SETS) {
        cout << "[ERR] The GBA only supports a single tileSet per map, this map has " << tileSets.size() << "." << endl;
        exit(EXIT_FAILURE);
    }

    auto tileSet = tileSets[0];
    GBAMap gbaMap("custom");
    auto tileSetConverter = new TileSetConverter(tileSet);

    cout << "- Converting tiles..." << endl;
    auto tileSetBytes = tileSetConverter->getTiles();
    gbaMap.setTileSet(tileSetBytes);

    cout << "- Converting palette..." << endl;
    auto paletteBytes = tileSetConverter->getPalette();
    gbaMap.setPalette(paletteBytes);

    cout << "Converting layers:" << endl;
    const auto& layers = tmxMap.getLayers();
    if (layers.size() > GBA_LAYERS) {
        cout << "[WARN] This map has " << layers.size() << ", which is " << GBA_LAYERS - layers.size()
             << " more than than the GBA has natively!" << endl;
    }

    auto *tileLayerConverter = new TileLayerConverter(tileSet.getFirstGID());
    for (const auto& layer : layers)
    {
        if (layer->getType() != tmx::Layer::Type::Tile)
            continue;

        cout << "- Converting Tile Layer: '" << layer->getName() << "'..." << endl;
        const auto tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());
        auto tileLayerBytes = tileLayerConverter->convert(tileLayer);
        gbaMap.addTileLayer(tileLayerBytes);
    }

    return gbaMap;
}