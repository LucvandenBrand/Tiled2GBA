#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <string>

using namespace std;

#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET   "\x1B[0m"

typedef enum LogLevel {
    INFO = 0,
    WARN = 1,
    ERROR = 2
} LogLevel;

class Logger {
public:
    static Logger* getInstance();

    void setLogLevel(LogLevel level);
    void log(LogLevel level, const string &message);
    virtual void operator() (LogLevel level, const string &message);

private:
    explicit Logger(ostream &logStream, LogLevel level);
    string levelToString(LogLevel level);

private:
    ostream &d_logStream;
    LogLevel d_level;
};

#endif // LOGGER_H