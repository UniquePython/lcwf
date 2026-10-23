#ifndef PRIVATE_TEXT_CASE_H_
#define PRIVATE_TEXT_CASE_H_

#include <stdbool.h>

typedef enum LCWF_TextCase
{
    LCWF_TEXT_CASE_LOWER,
    LCWF_TEXT_CASE_TITLE,
    LCWF_TEXT_CASE_UPPER,
    LCWF_TEXT_CASE_COUNT,

} LCWF_TextCase;

bool LCWF_IsValidCase(LCWF_TextCase textCase);

#endif
