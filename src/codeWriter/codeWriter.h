#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

using namespace std;

class CodeWriter {
public:
    explicit CodeWriter(const string &name);
    void makeArray(string name, vector<uint16_t> bytes);

    friend ostream& operator<<(ostream& os, const CodeWriter& codeWriter);

private:
    const int LINE_LENGTH = 15;

    string d_name;
    stringstream d_code, d_header;
};

#endif