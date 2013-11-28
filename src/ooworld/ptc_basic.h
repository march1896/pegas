#ifndef _PROTOCOL_BASIC_xECT_H_
#define _PROTOCOL_BASIC_xECT_H_

#include <ooworld/oo_model2.h>

typedef void     (*ptc_basic_destroy) (Object* me);
typedef Object*  (*ptc_basic_clone)   (const Object* me);
typedef bool     (*ptc_basic_equals)  (const Object* me, const Object* other);
typedef int      (*ptc_basic_compare) (const Object* me, const Object* other);
typedef hashcode (*ptc_basic_hashcode)(const Object* me);

struct basic_protocol {
	ptc_basic_destroy  __destroy;
	ptc_basic_clone    __clone;
	ptc_basic_equals   __equals;
	ptc_basic_compare  __compare;
	ptc_basic_hashcode __hashcode;
};

DECLARE_UID(basic_ptc_id);

void     ibasic_destroy(Object *me);
Object  *ibasic_clone(const Object *me); 
bool     ibasic_equals(const Object *me, const Object *other);
int      ibasic_compare(const Object *me, const Object *other);
hashcode ibasic_compare(const Object *me);

/*
declare_dispatch_function_0(basic, destroy, void);
declare_dispatch_function_const0(basic, clone, Object*);
declare_dispatch_function_const1(basic, equals, Object*, const Object*);
declare_dispatch_function_const1(basic, compare, Object*, const Object*);
declare_dispatch_function_const0(basic, hashcode, Object*, const Object*);
*/

#endif /* _PROTOCOL_BASIC_xECT_H_ */
