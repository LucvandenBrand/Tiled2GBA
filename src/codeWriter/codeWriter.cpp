#include "codeWriter.h"
#include <sstream>
#include <iomanip>

CodeWriter::CodeWriter(const string &name) {
    d_name = name;
}

void CodeWriter::makeArray(string name, vector<uint16_t> bytes) {
    const unsigned long numBytes = bytes.size();
    string definition = "const unsigned short " + d_name + name + "[" + to_string(numBytes) +"]";
    d_header << "#define " << d_name << name << "Length " << to_string(numBytes) << endl;
    d_header << "extern " << definition << ";" << endl << endl;
    d_code   << definition << " = {";

    for (int i = 0; i < numBytes; i++) {
        if (i > 0)
            d_code << ", ";
        if (i % LINE_LENGTH == 0)
            d_code << endl << "\t";

        d_code << "0x" << setfill('0') << setw(4) << hex << (int) bytes[i];
    }

    d_code << endl << "};" << endl << endl;
}

ostream& operator<<(ostream& os, const CodeWriter& codeWriter)
{
    os << codeWriter.d_name << ".h:" << endl << codeWriter.d_header.str();
    os << codeWriter.d_name << ".c:" << endl << codeWriter.d_code.str();
    return os;
}