#include "objectLayerConverter.hpp"
#include "../stringConverter/stringConverter.hpp"

vector<uint16_t> ObjectLayerConverter::convert(const tmx::ObjectGroup *objectGroup) {
    return convert(objectGroup->getObjects());
}

vector<uint16_t> ObjectLayerConverter::convert(const vector<tmx::Object> &objects) {
    vector<uint16_t> bytes;
    for (const tmx::Object &object : objects) {
        auto objectBytes = convert(object);
        bytes.insert(bytes.end(), objectBytes.begin(), objectBytes.end());
    }

    return bytes;
}

vector<uint16_t> ObjectLayerConverter::convert(const tmx::Object &object) {
    vector<uint16_t> bytes;

    auto id = (uint16_t) object.getUID();
    bytes.push_back(id);

    StringConverter stringConverter;
    vector<uint16_t> nameBytes = stringConverter.convert(object.getName());
    bytes.insert(bytes.end(), nameBytes.begin(), nameBytes.end());

    vector<uint16_t> typeBytes = stringConverter.convert(object.getType());
    bytes.insert(bytes.end(), typeBytes.begin(), typeBytes.end());

    return bytes;
}