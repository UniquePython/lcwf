#include "private/text_case.h"

bool LCWF_IsValidCase(LCWF_TextCase textCase)
{
    return LCWF_TEXT_CASE_LOWER <= textCase && textCase < LCWF_TEXT_CASE_COUNT;
}
