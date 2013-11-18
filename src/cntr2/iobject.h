#ifndef _INTERFACE_BASE_OBJECT_H_
#define _INTERFACE_BASE_OBJECT_H_

#include <oo_model.h>
#include <idef.h>

extern inline void     iobject_destroy        (object obj);
extern inline object   iobject_clone          (const_object obj);
extern inline bool     iobject_equals         (const_object obj, const_object other);
extern inline int      iobject_compare_to     (const_object obj, const_object other);
extern inline hashcode iobject_hashcode       (const_object obj);

extern inline bool     iobject_distinguishable(const_object obj_a, const_object obj_b);
extern inline bool     iobject_comparable     (const_object obj_a, const_object obj_b);
extern inline bool     iobject_hashable       (const_object obj);

extern unknown_traits object_traits;

typedef void     (*pf_iobject_destroy)    (object obj);
typedef object   (*pf_iobject_clone)      (const_object obj);
typedef bool     (*pf_iobject_equals)     (const_object obj, const_object other);
typedef int      (*pf_iobject_compare_to) (const_object obj, const_object other);
typedef hashcode (*pf_iobject_hashcode)   (const_object obj);

struct iobject_vtable {
	pf_iobject_destroy      __destroy;
	pf_iobject_clone        __clone;
	pf_iobject_equals       __equals;
	pf_iobject_compare_to   __compare_to;
	pf_iobject_hashcode     __hashcode;
};

#endif /* _INTERFACE_BASE_OBJECT_H_ */
