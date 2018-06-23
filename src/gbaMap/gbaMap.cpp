#include "gbaMap.hpp"
#include <sstream>
#include <iomanip>

GBAMap::GBAMap(const string &name) {
    d_name = name;
}

void GBAMap::setPalette(vector<uint16_t> &bytes) {
    d_palette = bytes;
}

void GBAMap::setTileSet(vector<uint16_t> &bytes) {
    d_tileSet = bytes;
}

void GBAMap::addTileLayer(vector<uint16_t> &bytes) {
    d_tileLayers.push_back(bytes);
}

void GBAMap::toCode(ostream &headerFile, ostream &codeFile) {
    makeArrayDeclaration(headerFile, d_name + "Palette", d_palette);
    makeArrayDefinition(codeFile, d_name + "Palette", d_palette);

    makeArrayDeclaration(headerFile, d_name + "TileSet", d_tileSet);
    makeArrayDefinition(codeFile, d_name + "TileSet", d_tileSet);

    for (int index = 0; index < d_tileLayers.size(); index++) {
        auto tileLayer = d_tileLayers[index];
        makeArrayDeclaration(headerFile, d_name + "TileMap" + to_string(index), tileLayer);
        makeArrayDefinition(codeFile, d_name + "TileMap" + to_string(index), tileLayer);
    }
}

void GBAMap::makeArrayDeclaration(ostream &headerStream, const string &name, vector<uint16_t> &bytes) {
    const unsigned long numBytes = bytes.size();
    string definition = "const unsigned short " + name + "[" + to_string(numBytes) +"]";
    headerStream << "#define " << name << "Length " << to_string(numBytes*2) << endl;
    headerStream << "extern " << definition << ";" << endl << endl;
}

void GBAMap::makeArrayDefinition(ostream &codeStream, const string &name, vector<uint16_t> &bytes) {
    const unsigned long numBytes = bytes.size();
    string definition = "const unsigned short " + name + "[" + to_string(numBytes) +"]";
    codeStream << definition << " = {";

    for (int i = 0; i < numBytes; i++) {
        if (i > 0)
            codeStream << ", ";
        if (i % LINE_LENGTH == 0)
            codeStream << endl << "\t";

        codeStream << "0x" << setfill('0') << setw(4) << hex << (int) bytes[i];
    }

    codeStream << endl << "};" << endl << endl;
}

