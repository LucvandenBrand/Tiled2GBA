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

void GBAMap::setTerrainMap(vector<uint16_t> &bytes) {
    d_terrainMap = bytes;
}

void GBAMap::addObjects(vector<uint16_t> &bytes) {
    d_objects.insert(d_objects.end(), bytes.begin(), bytes.end());
}

void GBAMap::setSize(unsigned mapWidth, unsigned mapHeight) {
    auto widthFlag  = (uint16_t) (mapWidth  == GBA_MAP_SIZE ? 0 : 1);
    auto heightFlag = (uint16_t) (mapHeight == GBA_MAP_SIZE ? 0 : 1);

    d_sizeFlag = (widthFlag | (heightFlag << 1)) << SIZE_FLAG_OFFSET;
}

void GBAMap::toCode(ostream &headerFile, ostream &codeFile) {
    makeFlagDefinition(headerFile, d_name + SIZE_FLAG_NAME, d_sizeFlag);
    vectorToCode(headerFile, codeFile, PALETTE_NAME, d_palette);
    vectorToCode(headerFile, codeFile, TILE_SET_NAME, d_tileSet);
    vectorToCode(headerFile, codeFile, TERRAIN_MAP_NAME, d_terrainMap);
    vectorToCode(headerFile, codeFile, OBJECTS_NAME, d_objects);
    vectorToCode(headerFile, codeFile, TILE_MAP_NAME, d_tileLayers);
}

void GBAMap::makeFlagDefinition(ostream &headerStream, const string &name, uint16_t flag) {
    headerStream << "#define " << name << " 0x" << setfill('0') << setw(4) << hex << (int) flag << endl << endl;
}

void GBAMap::vectorToCode(ostream &headerStream, ostream &codeStream, const string &name, vector<uint16_t> byteVector) {
    makeArrayDeclaration(headerStream, d_name + name, byteVector);
    makeArrayDefinition(codeStream, d_name + name, byteVector);
}

void GBAMap::vectorToCode(ostream &headerStream, ostream &codeStream, const string &name, vector<vector<uint16_t>> byteVectors) {
    for (int index = 0; index < byteVectors.size(); index++) {
        auto byteVectorName = name + to_string(index);
        auto byteVector = byteVectors[index];
        vectorToCode(headerStream, codeStream, byteVectorName, byteVector);
    }
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

void GBAMap::toBinary(ostream &binFile) {
    unsigned byteCount = 0;
    writeBinary(binFile, d_sizeFlag, &byteCount);
    writeBinary(binFile, (uint16_t) d_palette.size(), &byteCount);
    writeBinary(binFile, d_palette, &byteCount);

    writeBinary(binFile, PADDING_16_BIT, &byteCount);
    writeBinary(binFile, (uint16_t) d_tileSet.size(), &byteCount);
    writeBinary(binFile, d_tileSet, &byteCount);

    writeBinary(binFile, PADDING_16_BIT, &byteCount);
    writeBinary(binFile, (uint16_t) d_terrainMap.size(), &byteCount);
    writeBinary(binFile, d_terrainMap, &byteCount);

    writeBinary(binFile, (uint16_t) d_tileLayers.size(), &byteCount);
    if (!d_tileLayers.empty()) {
        writeBinary(binFile, (uint16_t) d_tileLayers[0].size(), &byteCount);
        writeBinary(binFile, d_tileLayers, &byteCount);
    }

    writeBinary(binFile, (uint16_t) d_objects.size(), &byteCount);
    writeBinary(binFile, d_objects, &byteCount);
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