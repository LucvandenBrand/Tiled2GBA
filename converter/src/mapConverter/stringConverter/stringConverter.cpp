#include <cstring>
#include "stringConverter.hpp"

vector<uint16_t> StringConverter::convert(const string &text) {
    vector<uint8_t> stringBytes = stringToByteVector(text);
    paddByteVector(stringBytes);
    vector<uint16_t> mergedStringBytes;
    auto numStringBytes = stringBytes.size();
    mergedStringBytes.push_back((uint16_t) (numStringBytes/2));

    for (unsigned index = 0; index < numStringBytes; index += 2) {
        auto firstChar = (uint16_t) (stringBytes[index+1] << 8 & 0xFF00);
        auto secondChar = (uint16_t) (stringBytes[index] & 0x00FF);
        uint16_t mergedChar = firstChar | secondChar;
        mergedStringBytes.push_back(mergedChar);
    }

    return mergedStringBytes;
}

vector<uint8_t> StringConverter::stringToByteVector(const string &text) {
    return vector<uint8_t>(text.begin(), text.end());
}

void StringConverter::paddByteVector(vector<uint8_t> &byteVector) {
    unsigned padding = getAlignmentOffset(byteVector.size());
    for (unsigned index = 0; index < padding; index++)
        byteVector.push_back(0);
}

unsigned StringConverter::getAlignmentOffset(unsigned long size) {
    return sizeof(uint32_t) - size % sizeof(uint32_t);
}