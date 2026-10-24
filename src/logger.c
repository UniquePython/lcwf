#include <stdarg.h>

#include "private/status.h"
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
        textCase = LCWF_TEXT_CASE_UPPER;

    if (!LCWF_IsValidLogLevel(level))
        return logLevelAsString[LCWF_LOG_LEVEL_COUNT][textCase];

    return logLevelAsString[level][textCase];
}

const char *LCWF_LogLevelToLowercaseString(LCWF_LogLevel level)
{
    return LCWF_LogLevelToString(level, LCWF_TEXT_CASE_LOWER);
}

const char *LCWF_LogLevelToTitlecaseString(LCWF_LogLevel level)
{
    return LCWF_LogLevelToString(level, LCWF_TEXT_CASE_TITLE);
}

const char *LCWF_LogLevelToUppercaseString(LCWF_LogLevel level)
{
    return LCWF_LogLevelToString(level, LCWF_TEXT_CASE_UPPER);
}

bool LCWF_IsValidLogLevel(LCWF_LogLevel level)
{
    return level >= LCWF_LOG_LEVEL_DEBUG && level < LCWF_LOG_LEVEL_COUNT;
}

bool LCWF_CreateLogger(LCWF_Logger **out, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (out == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    LCWF_Logger *logger;
    if (!LCWF_AllocAuto(&logger))
    {
        LCWF_SetStatus(LCWF_STATUS_ALLOC_FAILED, status);
        return false;
    }

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

bool LCWF_SetMinimumLogLevel(LCWF_Logger *logger, LCWF_LogLevel level, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (logger == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    if (!LCWF_IsValidLogLevel(level))
    {
        LCWF_SetStatus(LCWF_STATUS_INVALID_ENUM, status);
        return false;
    }

    logger->minimumLevel = level;
    return true;
}

LCWF_LogLevel LCWF_GetMinimumLogLevel(const LCWF_Logger *logger)
{
    if (logger == NULL)
        return LCWF_LOG_LEVEL_COUNT;

    return logger->minimumLevel;
}

bool LCWF_SetLogStream(LCWF_Logger *logger, LCWF_LogLevel level, FILE *stream, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (logger == NULL || stream == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    if (!LCWF_IsValidLogLevel(level))
    {
        LCWF_SetStatus(LCWF_STATUS_INVALID_ENUM, status);
        return false;
    }

    logger->streams[level] = stream;
    return true;
}

FILE *LCWF_GetLogStream(const LCWF_Logger *logger, LCWF_LogLevel level, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (logger == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return NULL;
    }

    if (!LCWF_IsValidLogLevel(level))
    {
        LCWF_SetStatus(LCWF_STATUS_INVALID_ENUM, status);
        return NULL;
    }

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
