#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

using namespace std;

class GBAMap {
public:
    explicit GBAMap(const string &name);

    void setPalette(vector<uint16_t> &bytes);
    void setTileSet(vector<uint16_t> &bytes);
    void addTileLayer(vector<uint16_t> &bytes);

    void toCode(ostream &headerFile, ostream &codeFile);

private:
    void makeArrayDeclaration(ostream &headerStream, const string &name, vector<uint16_t> &bytes);
    void makeArrayDefinition(ostream &codeStream, const string &name, vector<uint16_t> &bytes);

private:
    const int LINE_LENGTH = 15;

    vector<uint16_t> d_palette, d_tileSet;
    vector<vector<uint16_t>> d_tileLayers;

    string d_name;
};

#endif