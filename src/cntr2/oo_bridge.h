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

typedef unknown* (*pf_ibridge_clone)(const unknown *x, pf_alloc alc, void* heap);
typedef void     (*pf_ibridge_destroy)(const unknown *x, pf_dealloc alc, void* heap);
typedef compres  (*pf_ibridge_compare)(const unknown *x, const unknown *y);
typedef bool     (*pf_ibridge_equals)(const unknown *x, const unknown *y);
typedef hashcode (*pf_ibridge_hashcode)(const unknown *x);

typedef struct unknown_traits_t {
	pf_ibridge_destroy  __destroy;
	pf_ibridge_clone    __clone;
	pf_ibridge_compare  __compare_to;
	pf_ibridge_equals   __equals;
	pf_ibridge_hashcode __hashcode;
} unknown_traits;

typedef long long longint;
extern unknown_traits pointer_traits;
extern unknown_traits int_traits;
extern unknown_traits longint_traits;
extern unknown_traits float_traits;
extern unknown_traits double_traits;
extern unknown_traits char_traits;
extern unknown_traits bool_traits;
extern unknown_traits string_traits;

typedef void (*pf_ref_visit)(const unknown* __ref);
typedef void (*pf_ref_visit_v)(const unknown* __ref, void* context);

typedef void (*pf_ref_process)(unknown* __ref);
typedef void (*pf_ref_process_v)(unknown* __ref, void* context);

typedef compres (*pf_ref_compare)(const unknown* ref_a, const unknown* ref_b);
typedef compres (*pf_ref_compare_v)(const unknown* ref_a, const unknown* ref_b, void* context); 

#endif /* _OBJECT_REDUCE_TO_REFERENCE_H_ */
