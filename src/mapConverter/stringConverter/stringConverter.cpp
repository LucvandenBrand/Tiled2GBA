#include <cstring>
#include "stringConverter.hpp"

vector<uint16_t> StringConverter::convert(const string &text) {
    vector<uint16_t> bytes;

    string paddedText = paddString(text);
    auto numStringBytes = paddedText.length() + 1;

    char characters[numStringBytes];
    strcpy(characters, paddedText.c_str());

    for (unsigned index = 0; index < numStringBytes; index += 2) {
        auto mergedChar = (uint16_t) characters[index];
        mergedChar |= (uint16_t) characters[index+1] << 8;
        bytes.push_back(mergedChar);
    }

    return bytes;
}

string StringConverter::paddString(string text) {
    auto numStringBytes = text.length() + 1;
    auto remainingBytes = 4 - numStringBytes % 4;
    string appendedText = text;
    appendedText.append(remainingBytes, ' ');

    return appendedText;
}