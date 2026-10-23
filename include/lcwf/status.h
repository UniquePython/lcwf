#ifndef LCWF_STATUS_H_
#define LCWF_STATUS_H_

typedef enum LCWF_Status
{
    LCWF_STATUS_OK = 0,

    LCWF_STATUS_INVALID_PARAM,
    LCWF_STATUS_NULL_PARAM,
    LCWF_STATUS_INVALID_ENUM,
    LCWF_STATUS_INVALID_ADDRESS,

    LCWF_STATUS_NULL_CALLABLE,

    LCWF_STATUS_ALLOC_FAILED,

    LCWF_STATUS_READ_FAILED,
    LCWF_STATUS_WRITE_FAILED,

    LCWF_STATUS_SOCKET_FAILED,

    LCWF_STATUS_COUNT,

} LCWF_Status;

const char *LCWF_StatusToLowercaseString(LCWF_Status status);
const char *LCWF_StatusToTitlecaseString(LCWF_Status status);
const char *LCWF_StatusToUppercaseString(LCWF_Status status);

#endif
