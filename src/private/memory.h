#ifndef PRIVATE_MEMORY_H_
#define PRIVATE_MEMORY_H_

#include <stdbool.h>
#include <stddef.h>

bool LCWF_AllocImpl(size_t size, void **out);
bool LCWF_ReallocImpl(size_t size, void **out);
void LCWF_DeallocImpl(void **ptr);

#define LCWF_Alloc(size, out) LCWF_AllocImpl((size), (void **)(out))
#define LCWF_Realloc(size, out) LCWF_ReallocImpl((size), (void **)(out))
#define LCWF_Dealloc(ptr) LCWF_DeallocImpl((void **)(ptr))

#endif
