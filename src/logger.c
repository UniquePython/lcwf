#include <stdarg.h>
#include <stdlib.h>

#include "private/text_case.h"
#include "private/logger.h"
#include "private/memory.h"

static const char *const logLevelAsString[LCWF_LOG_LEVEL_COUNT + 1][LCWF_TEXT_CASE_COUNT] = {
    [LCWF_LOG_LEVEL_DEBUG] = {
        [LCWF_TEXT_CASE_LOWER] = "debug",
        [LCWF_TEXT_CASE_TITLE] = "Debug",
        [LCWF_TEXT_CASE_UPPER] = "DEBUG",
    },
    [LCWF_LOG_LEVEL_INFO] = {
        [LCWF_TEXT_CASE_LOWER] = "info",
        [LCWF_TEXT_CASE_TITLE] = "Info",
        [LCWF_TEXT_CASE_UPPER] = "INFO",
    },
    [LCWF_LOG_LEVEL_WARNING] = {
        [LCWF_TEXT_CASE_LOWER] = "warning",
        [LCWF_TEXT_CASE_TITLE] = "Warning",
        [LCWF_TEXT_CASE_UPPER] = "WARNING",
    },
    [LCWF_LOG_LEVEL_ERROR] = {
        [LCWF_TEXT_CASE_LOWER] = "error",
        [LCWF_TEXT_CASE_TITLE] = "Error",
        [LCWF_TEXT_CASE_UPPER] = "ERROR",
    },
    [LCWF_LOG_LEVEL_COUNT] = {
        [LCWF_TEXT_CASE_LOWER] = "unknown",
        [LCWF_TEXT_CASE_TITLE] = "Unknown",
        [LCWF_TEXT_CASE_UPPER] = "UNKNOWN",
    },
};

const char *LCWF_LogLevelToString(LCWF_LogLevel level, LCWF_TextCase textCase)
{
    if (!LCWF_IsValidCase(textCase))
        return logLevelAsString[LCWF_LOG_LEVEL_COUNT][LCWF_TEXT_CASE_UPPER];

    if (!LCWF_IsValidLogLevel(level))
        return logLevelAsString[LCWF_LOG_LEVEL_COUNT][textCase];

    return logLevelAsString[level][textCase];
}

bool LCWF_IsValidLogLevel(LCWF_LogLevel level)
{
    return level >= LCWF_LOG_LEVEL_DEBUG && level < LCWF_LOG_LEVEL_COUNT;
}

bool LCWF_CreateLogger(LCWF_Logger **out)
{
    if (out == NULL)
        return false;

    *out = NULL;

    LCWF_Logger *logger;
    if (!LCWF_Alloc(&logger))
        return false;

    logger->minimumLevel = LCWF_LOG_LEVEL_INFO;

    logger->streams[LCWF_LOG_LEVEL_DEBUG] = stdout;
    logger->streams[LCWF_LOG_LEVEL_INFO] = stdout;
    logger->streams[LCWF_LOG_LEVEL_WARNING] = stderr;
    logger->streams[LCWF_LOG_LEVEL_ERROR] = stderr;

    *out = logger;
    return true;
}

void LCWF_DestroyLogger(LCWF_Logger **logger)
{
    LCWF_Dealloc(logger);
}

bool LCWF_SetMinimumLogLevel(LCWF_Logger *logger, LCWF_LogLevel level)
{
    if (logger == NULL || !LCWF_IsValidLogLevel(level))
        return false;

    logger->minimumLevel = level;
    return true;
}

LCWF_LogLevel LCWF_GetMinimumLogLevel(const LCWF_Logger *logger)
{
    if (logger == NULL)
        return LCWF_LOG_LEVEL_COUNT;

    return logger->minimumLevel;
}

bool LCWF_SetLogStream(LCWF_Logger *logger, LCWF_LogLevel level, FILE *stream)
{
    if (logger == NULL || !LCWF_IsValidLogLevel(level) || stream == NULL)
        return false;

    logger->streams[level] = stream;
    return true;
}

FILE *LCWF_GetLogStream(const LCWF_Logger *logger, LCWF_LogLevel level)
{
    if (logger == NULL || !LCWF_IsValidLogLevel(level))
        return NULL;

    return logger->streams[level];
}

void LCWF_Log(LCWF_Logger *logger, LCWF_LogLevel level, const char *format, ...)
{
    if (logger == NULL || !LCWF_IsValidLogLevel(level) || level < logger->minimumLevel || format == NULL)
        return;

    FILE *stream = logger->streams[level];

    if (stream == NULL)
        return;

    va_list args;
    va_start(args, format);

    vfprintf(stream, format, args);
    fputc('\n', stream);

    va_end(args);
}
