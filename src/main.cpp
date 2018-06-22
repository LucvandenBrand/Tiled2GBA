#include <iostream>
#include <fstream>
#include "lib/tmxlite/Map.hpp"
#include "main.h"
#include "lib/tmxlite/TileLayer.hpp"
#include "tileLayerConverter/tileLayerConverter.h"
#include "gbaMap/gbaMap.h"
#include "tileSetConverter/tileSetConverter.h"
#include "lib/cxxopts/cxxopts.hpp"

int main(int argc, char **argv)
{
    cxxopts::Options options(argv[0], "Tiled Map to Gameboy Advance tile map converter");

    options
            .allow_unrecognised_options()
            .add_options()
                    ("h, help", "Print this help screen.")
                    ("i, input", "TMX map file.", cxxopts::value<string>(), "map.tmx")
                    ("o, output", "Output paths.", cxxopts::value<vector<string>>(), "files");

    options.parse_positional({"input", "output"});

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        cout << options.help() << endl;
        return EXIT_SUCCESS;
    }

    if (!result.count("input"))
    {
        cout << "Please provide an input file! See --help for more information." << endl;
        return EXIT_FAILURE;
    }

    string mapPath = result["input"].as<string>();

    if (!result.count("output")) {
        cout << "Please provide output information! See --help for more information." << endl;
        return EXIT_FAILURE;
    }

    vector<string> outPaths = result["output"].as<vector<string>>();

    if (outPaths.size() < 2) {
        cout << "Please provide a *.c and a *.h output file. See --help for more information." << endl;
        return EXIT_FAILURE;
    }

    tmx::Map map;
    if (!map.load(mapPath)) {
        return EXIT_FAILURE;
    };

    cout << "Tiled2GBA v0.1 by Luc van den Brand" << endl << endl;
    cout << "Loaded " << mapPath << " v" << map.getVersion().upper << "." << map.getVersion().lower << '.' << endl;

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

    cout << "Generating code...";

    ofstream codeFile, headerFile;
    codeFile.open (outPaths[0]);
    headerFile.open (outPaths[1]);
    gbaMap->toCode(headerFile, codeFile);
    codeFile.close();
    headerFile.close();

    cout << " done!" << endl << endl;
    cout << "Code stored in " << outPaths[0] << " and " << outPaths[1] << "." << endl;

    return EXIT_SUCCESS;
}
