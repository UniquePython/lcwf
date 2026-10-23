#include <stddef.h>

#include "private/status.h"

bool LCWF_IsValidStatus(LCWF_Status status)
{
    return status >= LCWF_STATUS_OK && status < LCWF_STATUS_COUNT;
}

void LCWF_SetStatus(LCWF_Status status, LCWF_Status *out)
{
    if (out == NULL)
        return;

    if (!LCWF_IsValidStatus(status))
    {
        *out = LCWF_STATUS_COUNT;
        return;
    }

    *out = status;
}

static const char *const statusAsString[LCWF_STATUS_COUNT + 1][LCWF_TEXT_CASE_COUNT] = {
    [LCWF_STATUS_OK] = {
        [LCWF_TEXT_CASE_LOWER] = "ok",
        [LCWF_TEXT_CASE_TITLE] = "Ok",
        [LCWF_TEXT_CASE_UPPER] = "OK",
    },
    [LCWF_STATUS_INVALID_PARAM] = {
        [LCWF_TEXT_CASE_LOWER] = "invalid param",
        [LCWF_TEXT_CASE_TITLE] = "Invalid Param",
        [LCWF_TEXT_CASE_UPPER] = "INVALID PARAM",
    },
    [LCWF_STATUS_NULL_PARAM] = {
        [LCWF_TEXT_CASE_LOWER] = "null param",
        [LCWF_TEXT_CASE_TITLE] = "Null Param",
        [LCWF_TEXT_CASE_UPPER] = "NULL PARAM",
    },
    [LCWF_STATUS_NULL_CALLABLE] = {
        [LCWF_TEXT_CASE_LOWER] = "null callable",
        [LCWF_TEXT_CASE_TITLE] = "Null Callable",
        [LCWF_TEXT_CASE_UPPER] = "NULL CALLABLE",
    },
    [LCWF_STATUS_ALLOC_FAILED] = {
        [LCWF_TEXT_CASE_LOWER] = "alloc failed",
        [LCWF_TEXT_CASE_TITLE] = "Alloc Failed",
        [LCWF_TEXT_CASE_UPPER] = "ALLOC FAILED",
    },
    [LCWF_STATUS_INVALID_ENUM] = {
        [LCWF_TEXT_CASE_LOWER] = "invalid enum",
        [LCWF_TEXT_CASE_TITLE] = "Invalid Enum",
        [LCWF_TEXT_CASE_UPPER] = "INVALID ENUM",
    },
    [LCWF_STATUS_READ_FAILED] = {
        [LCWF_TEXT_CASE_LOWER] = "read failed",
        [LCWF_TEXT_CASE_TITLE] = "Read Failed",
        [LCWF_TEXT_CASE_UPPER] = "READ FAILED",
    },
    [LCWF_STATUS_WRITE_FAILED] = {
        [LCWF_TEXT_CASE_LOWER] = "write failed",
        [LCWF_TEXT_CASE_TITLE] = "Write Failed",
        [LCWF_TEXT_CASE_UPPER] = "WRITE FAILED",
    },
    [LCWF_STATUS_INVALID_ADDRESS] = {
        [LCWF_TEXT_CASE_LOWER] = "invalid address",
        [LCWF_TEXT_CASE_TITLE] = "Invalid Address",
        [LCWF_TEXT_CASE_UPPER] = "INVALID ADDRESS",
    },
    [LCWF_STATUS_SOCKET_FAILED] = {
        [LCWF_TEXT_CASE_LOWER] = "socket failed",
        [LCWF_TEXT_CASE_TITLE] = "Socket Failed",
        [LCWF_TEXT_CASE_UPPER] = "SOCKET FAILED",
    },
    [LCWF_STATUS_COUNT] = {
        [LCWF_TEXT_CASE_LOWER] = "unknown",
        [LCWF_TEXT_CASE_TITLE] = "Unknown",
        [LCWF_TEXT_CASE_UPPER] = "UNKNOWN",
    },
};

const char *LCWF_StatusToString(LCWF_Status status, LCWF_TextCase textCase)
{
    if (!LCWF_IsValidCase(textCase))
        textCase = LCWF_TEXT_CASE_UPPER;

    if (!LCWF_IsValidStatus(status))
        return statusAsString[LCWF_STATUS_COUNT][textCase];

    return statusAsString[status][textCase];
}

const char *LCWF_StatusToLowercaseString(LCWF_Status status)
{
    return LCWF_StatusToString(status, LCWF_TEXT_CASE_LOWER);
}

const char *LCWF_StatusToTitlecaseString(LCWF_Status status)
{
    return LCWF_StatusToString(status, LCWF_TEXT_CASE_TITLE);
}

const char *LCWF_StatusToUppercaseString(LCWF_Status status)
{
    return LCWF_StatusToString(status, LCWF_TEXT_CASE_UPPER);
}
