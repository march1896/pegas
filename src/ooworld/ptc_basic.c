#include <ooworld/ptc_basic.h>

/*
DEFINE_UID(basic_ptc_id);
define_dispatch_function_0(basic, destroy, void);
define_dispatch_function_const0(basic, clone, Object*);
define_dispatch_function_const1(basic, equals, Object*, const Object*);
define_dispatch_function_const1(basic, compare, Object*, const Object*);
define_dispatch_function_const0(basic, hashcode, Object*, const Object*);
*/

DEFINE_UID(basic_ptc_id);

void ibasic_destroy(Object *me) {
	struct basic_protocol *ptc = me->__is_a->__get_protocol(basic_ptc_id);
	return ptc->__destroy(me);
}
Object *ibasic_clone(const Object *me) {
	struct basic_protocol *ptc = me->__is_a->__get_protocol(basic_ptc_id);
	return ptc->__clone(me);
}
bool     ibasic_equals(const Object *me, const Object *other);
int      ibasic_compare(const Object *me, const Object *other);
hashcode ibasic_compare(const Object *me);
