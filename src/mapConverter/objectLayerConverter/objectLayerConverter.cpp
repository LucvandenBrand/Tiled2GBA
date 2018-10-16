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

    uint32_t id = object.getUID();
    auto higherId = (uint16_t) (id << 16);
    bytes.push_back(higherId);
    auto lowerId = (uint16_t) id;
    bytes.push_back(lowerId);

    auto halfWidth = (int16_t) (object.getAABB().width / 2);
    auto halfHeight = (int16_t) (object.getAABB().height / 2);
    if (object.getTileID() > 0)
        halfHeight *= -1;

    auto xPosition = (uint16_t) object.getPosition().x + halfWidth;
    bytes.push_back(xPosition);
    auto yPosition = (uint16_t) object.getPosition().y + halfHeight;
    bytes.push_back(yPosition);

    StringConverter stringConverter;
    vector<uint16_t> nameBytes = stringConverter.convert(object.getName());
    bytes.insert(bytes.end(), nameBytes.begin(), nameBytes.end());

    vector<uint16_t> typeBytes = stringConverter.convert(object.getType());
    bytes.insert(bytes.end(), typeBytes.begin(), typeBytes.end());

    return bytes;
}