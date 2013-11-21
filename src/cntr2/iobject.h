#ifndef _INTERFACE_BASE_OBJECT_H_
#define _INTERFACE_BASE_OBJECT_H_

#include <oo_model.h>
#include <idef.h>

extern inline void     iobject_destroy        (Object* obj);
extern inline Object*  iobject_clone          (const Object* obj);
extern inline bool     iobject_equals         (const Object* obj, const Object* other);
extern inline int      iobject_compare_to     (const Object* obj, const Object* other);
extern inline hashcode iobject_hashcode       (const Object* obj);

extern inline bool     iobject_distinguishable(const Object* obj_a, const Object* obj_b);
extern inline bool     iobject_comparable     (const Object* obj_a, const Object* obj_b);
extern inline bool     iobject_hashable       (const Object* obj);

extern unknown_traits object_traits;

typedef void     (*pf_iobject_destroy)    (Object* obj);
typedef Object*  (*pf_iobject_clone)      (const Object* obj);
typedef bool     (*pf_iobject_equals)     (const Object* obj, const Object* other);
typedef int      (*pf_iobject_compare_to) (const Object* obj, const Object* other);
typedef hashcode (*pf_iobject_hashcode)   (const Object* obj);

struct iobject_vtable {
	pf_iobject_destroy      __destroy;
	pf_iobject_clone        __clone;
	pf_iobject_equals       __equals;
	pf_iobject_compare_to   __compare_to;
	pf_iobject_hashcode     __hashcode;
};

#endif /* _INTERFACE_BASE_OBJECT_H_ */
