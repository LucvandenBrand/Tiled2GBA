#include <iostream>
#include <fstream>
#include "lib/tmxlite/Map.hpp"
#include "main.hpp"
#include "gba/gbaMap/gbaMap.hpp"
#include "lib/cxxopts/cxxopts.hpp"
#include "mapConverter/mapConverter.hpp"
#include "log/logger.hpp"

void printHeader() {
    cout << PROGRAM_NAME << " v" << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH
         << " by " << AUTHOR << endl;
}

string pathToName(string path) {
    const size_t last_slash_idx = path.find_last_of("\\/");
    if (string::npos != last_slash_idx)
        path.erase(0, last_slash_idx + 1);

    const size_t period_idx = path.rfind('.');
    if (string::npos != period_idx)
        path.erase(period_idx);

    return path;
}

int main(int argc, char **argv)
{
    auto logger = Logger::getInstance();
    auto &log = *logger;

    vector<string> filePaths;
    bool toBinary = false;

    try {
        cxxopts::Options options(argv[0], "Allows you to convert Tiled TMX files to GBA compatible data.");

        options.allow_unrecognised_options().add_options()
                        ("h, help", "Print this help screen.")
                        ("v, verbose", "Print all log messages.")
                        ("w, warn", "Only print warnings and error messages.")
                        ("b, binary", "Export to binary.")
                        ("n, files", "File paths.", cxxopts::value<vector<string>>());

        options.parse_positional({"files"});

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            printHeader();
            cout << options.help() << endl;
            return EXIT_SUCCESS;
        }

        if (result.count("verbose")) {
            printHeader();
            logger->setLogLevel(INFO);
        } else if (result.count("warn")) {
            logger->setLogLevel(WARN);
        } else {
            logger->setLogLevel(ERROR);
        }

        if (result.count("binary"))
            toBinary = true;

        if (result.count("files"))
            filePaths = result["files"].as<vector<string>>();

    } catch (const cxxopts::OptionException& e) {
        log(ERROR, e.what());
        exit(EXIT_FAILURE);
    }

    if (filePaths.size() < 3 && !(toBinary && filePaths.size() > 1)) {
        log(ERROR, "Please provide input and output files as positional arguments.");
        return EXIT_FAILURE;
    }

    string mapPath = filePaths[0];
    tmx::Map tmxMap;
    if (!tmxMap.load(mapPath))
        return EXIT_FAILURE;

    log(INFO, "Loaded '" + mapPath + "'.");

    string mapName = pathToName(mapPath);
    MapConverter mapConverter;
    GBAMap gbaMap = mapConverter.convert(mapName, tmxMap);

    if (toBinary) {
        log(INFO, "Generating binary.");

        string filePath = filePaths[1];
        ofstream binFile;
        binFile.open(filePath, ios_base::out | ios_base::binary);
        binFile.imbue(locale::classic());

        gbaMap.toBinary(binFile);

        binFile.close();

        log(INFO, "Binary stored in '" + filePath + "'.");
    } else {
        log(INFO, "Generating code.");

        string cFilePath = filePaths[1];
        string hFilePath = filePaths[2];
        ofstream codeFile, headerFile;
        codeFile.open(cFilePath);
        headerFile.open(hFilePath);

        gbaMap.toCode(headerFile, codeFile);

        codeFile.close();
        headerFile.close();

        log(INFO, "Code stored in '" + cFilePath + "' and '" + hFilePath + "'.");
    }

    return EXIT_SUCCESS;
}
