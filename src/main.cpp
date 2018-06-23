#include <iostream>
#include <fstream>
#include "lib/tmxlite/Map.hpp"
#include "main.hpp"
#include "gbaMap/gbaMap.hpp"
#include "lib/cxxopts/cxxopts.hpp"
#include "mapConverter/mapConverter.hpp"
#include "log/logger.hpp"

void printHeader() {
    cout << PROGRAM_NAME << " v" << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH
         << " by " << AUTHOR << endl;
    cout << "-------------------------------------" << endl;
}

int main(int argc, char **argv)
{
    cxxopts::Options options(argv[0], "Tiled Map file to GameBoy Advance tile map data converter.");

    options
            .allow_unrecognised_options()
            .add_options()
                    ("h, help", "Print this help screen.")
                    ("v, verbose", "Print all log messages.")
                    ("w, warn", "Only print warnings and error messages.")
                    ("i, input", "TMX map file.", cxxopts::value<string>(), "map.tmx")
                    ("o, output", "Output paths.", cxxopts::value<vector<string>>(), "files");

    options.parse_positional({"input", "output"});

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        printHeader();
        cout << options.help() << endl;
        return EXIT_SUCCESS;
    }

    auto logger = Logger::getInstance();
    if (result.count("verbose")) {
        printHeader();
        logger->setLogLevel(INFO);
    } else if (result.count("warn")) {
        logger->setLogLevel(WARN);
    } else {
        logger->setLogLevel(ERROR);
    }
    auto log = *logger;

    if (!result.count("input"))
    {
        log(ERROR, "Please provide an input file! See --help for more information.");
        return EXIT_FAILURE;
    }

    string mapPath = result["input"].as<string>();

    if (!result.count("output")) {
        log(ERROR, "Please provide output information! See --help for more information.");
        return EXIT_FAILURE;
    }

    vector<string> outPaths = result["output"].as<vector<string>>();

    if (outPaths.size() < 2) {
        log(ERROR, "Please provide a *.c and a *.h output file. See --help for more information.");
        return EXIT_FAILURE;
    }

    tmx::Map tmxMap;
    if (!tmxMap.load(mapPath)) {
        return EXIT_FAILURE;
    };

    log(INFO, "Loaded '" + mapPath + "'.");

    MapConverter mapConverter;
    GBAMap gbaMap = mapConverter.convert(tmxMap);

    log(INFO, "Generating code.");

    string cFilePath = outPaths[0];
    string hFilePath = outPaths[1];
    ofstream codeFile, headerFile;
    codeFile.open (cFilePath);
    headerFile.open (hFilePath);

    gbaMap.toCode(headerFile, codeFile);

    codeFile.close();
    headerFile.close();

    log(INFO, "Code stored in '" + cFilePath + "' and '" + hFilePath + "'.");

    return EXIT_SUCCESS;
}
