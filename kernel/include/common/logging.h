#ifndef LOGGING_H
#define LOGGING_H

/**
 * @brief The type of the log
 */
enum logType {
    LOG_DEBUG,
    LOG_SUCCESS,
    LOG_WARN,
    LOG_ERROR,
};

#define LOG_BUFFER_DIM 1024

void log_line(enum logType logLevel, char *fmt, ...);

#endif // LOGGING_H