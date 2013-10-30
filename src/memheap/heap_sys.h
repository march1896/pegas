#ifndef _HEAP_SYSTEM_DEFAULT_H_
#define _HEAP_SYSTEM_DEFAULT_H_

#include <memheap/heap_def.h>

/* Implement the following interface one by one */
/*
typedef void* (*pf_alloc_c)   (void* pheap, int size);
typedef void* (*pf_alloc_v)   (void* pheap, int size, const char* file, int line);

typedef bool (*pf_dealloc_c)  (void* pheap, void* buff);
typedef bool (*pf_dealloc_v)  (void* pheap, void* buff, const char* file, int line);
*/

void* heap_sysd_alloc_c  (void* h, int size);
void* heap_sysd_alloc_v  (void* h, int size, const char* file ,int line);

bool  heap_sysd_dealloc_c(void* h, void* buff);
bool  heap_sysd_dealloc_v(void* h, void* buff, const char* file, int line);

#ifdef _VERBOSE_ALLOC_DEALLOC_
#define heap_sysd_alloc   heap_sysd_alloc_v
#define heap_sysd_dealloc heap_sysd_dealloc_v
#else 
#define heap_sysd_alloc   heap_sysd_alloc_c
#define heap_sysd_dealloc heap_sysd_dealloc_c
#endif

#endif /* _HEAP_SYSTEM_DEFAULT_H_ */
