#ifndef _OBJECT_REDUCE_TO_REFERENCE_H_
#define _OBJECT_REDUCE_TO_REFERENCE_H_

/* 
 * C is not an object-oriented language, (even c++ is not, object is not the base element of the language, in fact,
 * all languages that have to abstract the hardware are not good to be fully object-oriented), we have to handle the 
 * the case when object reduce to raw pointers. For example,
 * the element stored in container are most likely to be raw pointers, but not objects.
 * This module defines some common basic operation for the raw-pointers-objects.
 * NOTE: it's a pity that so many "const" are added only for decoration.
 */

#include <heap_def.h>

struct heap_context {
	pf_alloc   alloc;
	pf_dealloc dealloc;
	void*      heap;
};

typedef void (*pf_ref_clone)(const void* __ref, struct heap_context* heap);

typedef void (*pf_ref_clone_v)(const void* __ref, pf_alloc alc, void* heap);

typedef void (*pf_ref_destroy)(void* __ref);

typedef void (*pf_ref_destroy_v)(void* __ref, pf_dealloc alc, void* heap);

typedef void (*pf_ref_visit)(const void* __ref);

typedef void (*pf_ref_visit_v)(const void* __ref, void* context);

typedef void (*pf_ref_process)(void* __ref);

typedef void (*pf_ref_process_v)(void* __ref, void* context);

typedef pf_ref_process   pf_ref_dispose;
typedef pf_ref_process_v pf_ref_dispose_v;

typedef int  (*pf_ref_compare)(const void* ref_a, const void* ref_b);

#endif /* _OBJECT_REDUCE_TO_REFERENCE_H_ */
