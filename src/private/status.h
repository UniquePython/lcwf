#ifndef PRIVATE_STATUS_H_
#define PRIVATE_STATUS_H_

#include "lcwf/status.h"
#include "private/text_case.h"

void LCWF_SetStatus(LCWF_Status status, LCWF_Status *out);
const char *LCWF_StatusToString(LCWF_Status status, LCWF_TextCase textCase);

#endif
