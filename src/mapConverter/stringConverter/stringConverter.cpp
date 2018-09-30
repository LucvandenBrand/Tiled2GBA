#include <cstring>
#include "stringConverter.hpp"

vector<uint16_t> StringConverter::convert(const string &text) {
    const char* byteArray = text.c_str();
    const char* paddedByteArray = createPaddedByteArray(byteArray);
    auto numBytes = getByteArraySize(paddedByteArray);
    numBytes += getAlignmentOffset(numBytes);
    vector<uint16_t> bytes;

    for (unsigned index = 0; index < numBytes; index += 2) {
        auto mergedChar = (uint16_t) paddedByteArray[index] << 8;
        mergedChar |= (uint16_t) paddedByteArray[index+1];
        bytes.push_back(mergedChar);
    }

    return bytes;
}

const char* StringConverter::createPaddedByteArray(const char* byteArray) {
    auto numBytes = getByteArraySize(byteArray);
    unsigned remainingBytes = getAlignmentOffset(numBytes);
    unsigned numBytesPadded = numBytes + remainingBytes;
    char* paddedByteArray = new char[numBytesPadded];

    for (unsigned index = 0; index < numBytes; index++)
        paddedByteArray[index] = byteArray[index];
    for (unsigned index = numBytes; index < numBytesPadded; index++)
        paddedByteArray[index] = '\0';

    return paddedByteArray;
}

unsigned StringConverter::getByteArraySize(const char *byteArray) {
    return (unsigned) strlen(byteArray) + 1;
}

unsigned StringConverter::getAlignmentOffset(unsigned size) {
    return sizeof(uint32_t) - size % sizeof(uint32_t);
}