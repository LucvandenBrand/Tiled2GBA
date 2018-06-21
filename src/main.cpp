#include <iostream>
#include "lib/tmxlite/Map.hpp"
#include "main.h"
#include "lib/tmxlite/TileLayer.hpp"
#include "tileLayerConverter/tileLayerConverter.h"
#include "gbaMap/gbaMap.h"
#include "tileSetConverter/tileSetConverter.h"

int main(int argc, char **argv)
{
    if (argc < NUM_ARGS) {
        cout << "Usage: " << argv[0] << " mapFile.tmx" << endl;
        return EXIT_FAILURE;
    }

    string mapPath = argv[1];
    tmx::Map map;
    if (!map.load(mapPath)) {
        cout << "[ERR] Problem whilst loading " << mapPath << '!' << endl;
        return EXIT_FAILURE;
    };

    cout << "Loaded " << mapPath << " version " << map.getVersion().upper << "." << map.getVersion().lower << '.' << endl;

    auto tileSize = map.getTileSize();
    if (tileSize.x != TILE_SIZE || tileSize.y != TILE_SIZE) {
        cout << "[ERR] The tile size of " << tileSize.x << 'x' << tileSize.y << " is not compatible with the GBA." << endl;
        cout << "The GBA expects 8x8 tiles." << endl;
        return EXIT_FAILURE;
    }

    cout << "Converting tileSet:" << endl;
    auto tileSets= map.getTilesets();
    if (tileSets.size() != NUM_TILE_SETS) {
        cout << "[ERR] The GBA only supports a single tileSet per map, this map has " << tileSets.size() << "." << endl;
        return EXIT_FAILURE;
    }

    auto tileSet = tileSets[0];
    auto *gbaMap = new GBAMap("custom");
    auto tileSetConverter = new TileSetConverter(tileSet);

    cout << "- Converting tiles..." << endl;
    auto tileSetBytes = tileSetConverter->getTiles();
    gbaMap->setTileSet(tileSetBytes);

    cout << "- Converting palette..." << endl;
    auto paletteBytes = tileSetConverter->getPalette();
    gbaMap->setPalette(paletteBytes);

    cout << "Converting layers:" << endl;
    const auto& layers = map.getLayers();
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
        gbaMap->addTileLayer(tileLayerBytes);
    }

    cout << endl << "Results:" << endl;
    gbaMap->toCode(cout, cout);

    cout << "Done!" << endl;
    return EXIT_SUCCESS;
}
