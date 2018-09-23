#ifndef OBJECT_LAYER_CONVERTER_H
#define OBJECT_LAYER_CONVERTER_H

#include <vector>
#include "../../lib/tmxlite/ObjectGroup.hpp"

using namespace std;

/**
 * Converts an Object Layer to binary data describing the objects.
 */
class ObjectLayerConverter {
public:
    /**
     * Convert an Object Layer.
     * @param objectGroup The list of objects in the layer.
     */
    vector<uint16_t> convert(const tmx::ObjectGroup *objectGroup);

private:
    vector<uint16_t> convert(const vector<tmx::Object> &objects);
    vector<uint16_t> convert(const tmx::Object &object);

};

#endif // OBJECT_LAYER_CONVERTER_H