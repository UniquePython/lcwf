
#ifndef LCWF_LOGGER_H_
#define LCWF_LOGGER_H_

#include <stdbool.h>
#include <stdio.h>

#include "lcwf/status.h"

typedef struct LCWF_Logger LCWF_Logger;

typedef enum LCWF_LogLevel
{
    LCWF_LOG_LEVEL_DEBUG = 0,
    LCWF_LOG_LEVEL_INFO,
    LCWF_LOG_LEVEL_WARNING,
    LCWF_LOG_LEVEL_ERROR,
    LCWF_LOG_LEVEL_COUNT,
} LCWF_LogLevel;

const char *LCWF_LogLevelToLowercaseString(LCWF_LogLevel level);
const char *LCWF_LogLevelToTitlecaseString(LCWF_LogLevel level);
const char *LCWF_LogLevelToUppercaseString(LCWF_LogLevel level);

bool LCWF_CreateLogger(LCWF_Logger **out, LCWF_Status *status);
void LCWF_DestroyLogger(LCWF_Logger **logger);

bool LCWF_SetMinimumLogLevel(LCWF_Logger *logger, LCWF_LogLevel level, LCWF_Status *status);

LCWF_LogLevel LCWF_GetMinimumLogLevel(const LCWF_Logger *logger);

bool LCWF_SetLogStream(LCWF_Logger *logger, LCWF_LogLevel level, FILE *streams, LCWF_Status *status);
FILE *LCWF_GetLogStream(const LCWF_Logger *logger, LCWF_LogLevel level, LCWF_Status *status);

void LCWF_Log(LCWF_Logger *logger, LCWF_LogLevel level, const char *format, ...);

#endif
