#include "gbaMap.hpp"
#include "../background.h"
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

void GBAMap::setSize(unsigned mapWidth, unsigned mapHeight) {
    auto widthFlag  = (uint16_t) (mapWidth  == GBA_MAP_SIZE ? 0 : 1);
    auto heightFlag = (uint16_t) (mapHeight == GBA_MAP_SIZE ? 0 : 1);

    d_sizeFlag = (widthFlag | (heightFlag << 1)) << SIZE_FLAG_OFFSET;
}

void GBAMap::toCode(ostream &headerFile, ostream &codeFile) {
    makeFlagDefinition(headerFile, d_name + SIZE_FLAG_NAME, d_sizeFlag);
    makeArrayDeclaration(headerFile, d_name + PALETTE_NAME, d_palette);
    makeArrayDefinition(codeFile, d_name + PALETTE_NAME, d_palette);

    makeArrayDeclaration(headerFile, d_name + TILE_SET_NAME, d_tileSet);
    makeArrayDefinition(codeFile, d_name + TILE_SET_NAME, d_tileSet);

    for (int index = 0; index < d_tileLayers.size(); index++) {
        auto tileLayer = d_tileLayers[index];
        makeArrayDeclaration(headerFile, d_name + TILE_MAP_NAME + to_string(index), tileLayer);
        makeArrayDefinition(codeFile, d_name + TILE_MAP_NAME + to_string(index), tileLayer);
    }
}

void GBAMap::toBinary(ostream &binFile) {
    unsigned byteCount = 0;
    writeBinary(binFile, d_sizeFlag, &byteCount);
    writeBinary(binFile, (u_int16_t) d_palette.size(), &byteCount);
    writeBinary(binFile, d_palette, &byteCount);

    writeBinary(binFile, PADDING_16_BIT, &byteCount);
    writeBinary(binFile, (u_int16_t) d_tileSet.size(), &byteCount);
    writeBinary(binFile, d_tileSet, &byteCount);

    writeBinary(binFile, (u_int16_t) d_tileLayers.size(), &byteCount);
    if (!d_tileLayers.empty()) {
        writeBinary(binFile, (u_int16_t) d_tileLayers[0].size(), &byteCount);
        writeBinary(binFile, d_tileLayers, &byteCount);
    }
}

void GBAMap::makeFlagDefinition(ostream &headerStream, const string &name, uint16_t flag) {
    headerStream << "#define " << name << " 0x" << setfill('0') << setw(4) << hex << (int) flag << endl << endl;
}

void GBAMap::makeArrayDeclaration(ostream &headerStream, const string &name, vector<uint16_t> &bytes) {
    const unsigned long numValues = bytes.size();
    string definition = "const unsigned short " + name + "[" + to_string(numValues) +"]";
    headerStream << "#define " << name << "Length " << to_string(numValues) << endl;
    headerStream << "extern " << definition << ";" << endl << endl;
}

void GBAMap::makeArrayDefinition(ostream &codeStream, const string &name, vector<uint16_t> &bytes) {
    const unsigned long numValues = bytes.size();
    string definition = "const unsigned short " + name + "[" + to_string(numValues) +"]";
    codeStream << definition << " = {";

    for (int i = 0; i < numValues; i++) {
        if (i > 0)
            codeStream << ", ";
        if (i % LINE_LENGTH == 0)
            codeStream << endl << "\t";

        auto value = bytes[i];
        unsigned numNibbles = sizeof(value) * 2;
        codeStream << "0x" << setfill('0') << setw(numNibbles) << hex << value;
    }

    codeStream << endl << "};" << endl << endl;
}

template<typename T>
ostream& GBAMap::writeBinary(ostream &stream, const T &value, unsigned *byteCount) {
    *byteCount += sizeof(T);
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
ostream& GBAMap::writeBinary(ostream &stream, const vector<T> &vec, unsigned *byteCount) {
    for (const T &value : vec)
        writeBinary(stream, value, byteCount);
    return stream;
}