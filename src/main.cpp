#include <iostream>
#include <fstream>
#include "lib/tmxlite/Map.hpp"
#include "main.hpp"
#include "gbaMap/gbaMap.hpp"
#include "lib/cxxopts/cxxopts.hpp"
#include "mapConverter/mapConverter.hpp"

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

    tmx::Map tmxMap;
    if (!tmxMap.load(mapPath)) {
        return EXIT_FAILURE;
    };

    cout << "Tiled2GBA v0.1 by Luc van den Brand" << endl << endl;
    cout << "Loaded " << mapPath << " v" << tmxMap.getVersion().upper << "." << tmxMap.getVersion().lower << '.' << endl;

    MapConverter mapConverter;
    GBAMap gbaMap = mapConverter.convert(tmxMap);

    cout << "Generating code...";

    ofstream codeFile, headerFile;
    codeFile.open (outPaths[0]);
    headerFile.open (outPaths[1]);
    gbaMap.toCode(headerFile, codeFile);
    codeFile.close();
    headerFile.close();

    cout << " done!" << endl << endl;
    cout << "Code stored in " << outPaths[0] << " and " << outPaths[1] << "." << endl;

    return EXIT_SUCCESS;
}
