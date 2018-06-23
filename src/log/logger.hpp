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

/**
 * Simple logger.
 */
class Logger {
public:
    /**
     * Return a singleton instance of the logger.
     * @return The singleton instance
     */
    static Logger* getInstance();

    /**
     * Set the level of messages displayed to the user.
     * @param level The log level.
     */
    void setLogLevel(LogLevel level);

    /**
     * Log a message of a particular level.
     * @param level The logging level.
     * @param message The message to log.
     */
    void log(LogLevel level, const string &message);

    /**
     * Log a message by using this object as a functor.
     * @param level The logging level.
     * @param message The message to log.
     */
    virtual void operator() (LogLevel level, const string &message);

private:
    explicit Logger(ostream &logStream, LogLevel level);
    string levelToString(LogLevel level);

    ostream &d_logStream;
    LogLevel d_level;
};

#endif // LOGGER_H