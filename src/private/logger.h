
#ifndef PRIVATE_LOGGER_H_
#define PRIVATE_LOGGER_H_

#include "lcwf/logger.h"
#include "private/text_case.h"

struct LCWF_Logger
{
    LCWF_LogLevel minimumLevel;
    FILE *streams[LCWF_LOG_LEVEL_COUNT];
};

bool LCWF_IsValidLogLevel(LCWF_LogLevel level);
const char *LCWF_LogLevelToString(LCWF_LogLevel level, LCWF_TextCase textCase);

#endif
