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

#include <memheap/heap_def.h>
#include <cntr2/oo_model.h>

typedef unknown (*pf_ref_clone)(const_unknown __ref);
typedef unknown (*pf_ref_clone_v)(const_unknown __ref, pf_alloc alc, void* heap);

typedef void (*pf_ref_destroy)(unknown __ref);
typedef void (*pf_ref_destroy_v)(unknown __ref, pf_dealloc alc, void* heap);

typedef void (*pf_ref_visit)(const_unknown __ref);
typedef void (*pf_ref_visit_v)(const_unknown __ref, void* context);

typedef void (*pf_ref_process)(unknown __ref);
typedef void (*pf_ref_process_v)(unknown __ref, void* context);

typedef void (*pf_ref_dispose)(unknown __ref);
typedef void (*pf_ref_dispose_v)(unknown __ref, void* context);

typedef int  (*pf_ref_compare)(const_unknown ref_a, const_unknown ref_b);
typedef int  (*pf_ref_compare_v)(const_unknown ref_a, const_unknown ref_b, void* context); 

typedef bool (*pf_ref_equals)(const_unknown ref_a, const_unknown ref_b);
typedef bool (*pf_ref_equals_v)(const_unknown ref_a, const_unknown ref_b, void* context);

struct type_traits {
	pf_ref_clone_v __clone;
	pf_ref_destroy_v __destroy;
	pf_ref_equals  __equals;
	pf_ref_compare __compare;
};

extern struct type_traits __global_integer_traits;
extern struct type_traits __global_decimal_traits;
extern struct type_traits __global_pointer_traits;

#define Integer __global_integer_traits
#define Decimal __global_decimal_traits
#define Pointer __global_pointer_traits

void* pointer_clone_v(const_unknown __ref, pf_alloc alc, void* heap);
void  pointer_destroy_v(unknown __ref, pf_dealloc dlc, void* heap);
bool  pointer_equals_v(const_unknown ref_a, const_unknown ref_b, void* context);

int   pointer_compare(const_unknown ref_a, const_unknown ref_b);
int   pointer_compare_v(const_unknown ref_a, const_unknown ref_b, void* context);

#endif /* _OBJECT_REDUCE_TO_REFERENCE_H_ */
