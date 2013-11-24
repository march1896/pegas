#include <cntr2/oo_model.h>

inline Object* __object_from_interface(const _interface* inf) {
	const _interface* inf0 = inf - (intptr_t)inf->__offset;
	Object* obj = container_of(inf0, struct base_object, __iftable[0]);

	return obj;
}

inline bool __is_object(const unknown* x) {
	const Object* obj = (const Object*)x;
	if (obj->__offset == x) {
		//dbg_assert(obj->__cast(x, OBJECT_ME) == x);
		return true;
	}

	return false;
}

inline bool __is_interface(const unknown *x) {
	const _interface* inf = (const _interface*)x;
	dbg_assert((intptr_t)(inf->__offset) <= __MAX_NUM_INTERFACE_PER_OBJECT);

	{
		const Object* obj = __object_from_interface(inf);
		if (__is_object((unknown*)obj)) {
			return true;
		}
	}

	return false;
}

inline unknown* __cast(const unknown* x, unique_id id) {
	if (__is_object(x)) {
		Object* obj = (Object*)x;
		return obj->__cast(obj, id);
	} 
	else if (__is_interface(x)) {
		Object* obj = (Object*)__object_from_interface((_interface*)x);
		return obj->__cast(obj, id);
	}
	dbg_assert(false);

	return NULL;
}

inline _interface* __fast_cast(const Object* obj, int ifoffset) {
	dbg_assert(__is_object(obj));
	return (_interface*)&obj->__iftable[ifoffset];
}

