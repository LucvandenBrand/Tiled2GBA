#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

using namespace std;

/**
 * Stores data in GBA format.
 */
class GBAMap {
public:
    /**
     * Construct a GBAMap to hold GBA Map data.
     * @param name The name of the map.
     */
    explicit GBAMap(const string &name);

    /**
     * Set the palette of the map.
     * @param bytes The color data.
     */
    void setPalette(vector<uint16_t> &bytes);

    /**
     * Set the Char block of the map.
     * @param bytes The Char block data.
     */
    void setTileSet(vector<uint16_t> &bytes);

    /**
     * Set the tile-terrain mapping.
     * @param bytes The terrain types.
     */
    void setTerrainMap(vector<uint16_t> &bytes);

    /**
     * Set the size of the map. Assumes the width and height are valid.
     * The width and height are converted to a flag for the GBA hardware to work with.
     * @param mapWidth The width of the map.
     * @param mapHeight The height of the map.
     */
    void setSize(unsigned mapWidth, unsigned mapHeight);

    /**
     * Add a screen block to the map.
     * @param bytes The Screen block data.
     */
    void addTileLayer(vector<uint16_t> &bytes);

    /**
     * Add a collection of objects to the map.
     * @param bytes The objects in byte data.
     */
    void addObjects(vector<uint16_t> &bytes);

    /**
     * Convert the map data to C code.
     * @param headerFile The header file to store declarations in.
     * @param codeFile The code file to store definitions in.
     */
    void toCode(ostream &headerFile, ostream &codeFile);

    /**
     * Convert the map data to binary data.
     * @param binFile  The binary file to store the data in.
     */
    void toBinary(ostream &binFile);

private:
    void makeFlagDefinition(ostream &headerStream, const string &name, uint16_t flag);
    void vectorToCode(ostream &headerStream, ostream &codeStream, const string &name, vector<uint16_t> byteVector);
    void vectorToCode(ostream &headerStream, ostream &codeStream, const string &name, vector<vector<uint16_t>> byteVectors);
    void makeArrayDeclaration(ostream &headerStream, const string &name, vector<uint16_t> &bytes);
    void makeArrayDefinition(ostream &codeStream, const string &name, vector<uint16_t> &bytes);

    template<typename T>
    ostream& writeBinary(ostream &stream, const T& value, unsigned *byteCount);
    template<typename T>
    ostream& writeBinary(ostream &stream, const vector<T> &vec, unsigned *byteCount);

    const int SIZE_FLAG_OFFSET = 14;
    const int LINE_LENGTH = 15;

    const char *SIZE_FLAG_NAME = "SizeFlag";
    const char *PALETTE_NAME = "Palette";
    const char *TILE_SET_NAME = "TileSet";
    const char *TILE_MAP_NAME = "TileMap";
    const char *TERRAIN_MAP_NAME = "TerrainMap";
    const char *OBJECTS_NAME = "Objects";

    const uint16_t PADDING_16_BIT = 0x0000;

    uint16_t d_sizeFlag;
    vector<uint16_t> d_palette, d_tileSet, d_terrainMap, d_objects;
    vector<vector<uint16_t>> d_tileLayers;

    string d_name;
};

#endif