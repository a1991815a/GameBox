#ifndef __GBASSERT__
#define __GBASSERT__
#include <assert.h>

#define GB_ASSERT(cond) assert(cond)
#define GBASSERT(cond) GB_ASSERT(cond)

#endif