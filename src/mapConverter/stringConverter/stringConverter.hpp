#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <vector>
#include <string>

using namespace std;

/**
 * Converts strings into binary data readable by the GBA.
 */
class StringConverter {
public:
    /**
     * Convert a string into a vector of 2-byte values.
     * It adds null characters to the vector in order preserve proper 32-bit alignment.
     * @param text The text to convert.
     * @return A vector of 2-byte values.
     */
    vector<uint16_t> convert(const string &text);

private:
    const char* createPaddedByteArray(const char* byteArray);
    unsigned getByteArraySize(const char* byteArray);
    unsigned getAlignmentOffset(unsigned size);
};

#endif