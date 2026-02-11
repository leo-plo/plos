#ifndef LOGGING_H
#define LOGGING_H

enum logType {
    LOG_DEBUG,
    LOG_WARN,
    LOG_ERROR,
    LOG_SUCCESS
};

enum logOutput {
    LOG_SERIAL,
    LOG_FRAMEBUFFER
};

void log_init(enum logOutput out);
void log_log_line(enum logType logLevel, char *fmt, ...);

#endif // LOGGING_H