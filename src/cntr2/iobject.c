#include <iobject.h>

/* object knows how to clone itself, so alc and heap are useless */
static unknown object_clone(const_unknown x, pf_alloc alc, void* heap) {
	_interface _inf = (_interface)__cast(x, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	return ((struct iobject_vtable*)_inf->__vtable)->__clone((object)x);
}
/* object knows how to destroy itself, so dlc and heap are useless */
static void object_destroy(const_unknown x, pf_dealloc alc, void* heap) {
	_interface _inf = (_interface)__cast(x, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	((struct iobject_vtable*)_inf->__vtable)->__destroy((object)x);
}

static int object_compare_to(const_unknown x, const_unknown y) {
	_interface _inf_a = (_interface)__cast((unknown)x, IOBJECT_ID);
	_interface _inf_b = (_interface)__cast((unknown)y, IOBJECT_ID);

	/* first, two objects are both objects */
	if (_inf_a == NULL || _inf_b == NULL)
		rt_error("object_compare: at least one is not objects");

	/* first, two objects belongs to the same type */
	if (_inf_a->__vtable != _inf_b->__vtable)
		rt_error("object_compare: two objects are not the same type");

	/* third, the object has equals method */
	if (((struct iobject_vtable*)_inf_a->__vtable)->__compare_to == NULL)
		rt_error("object_compare: object does not support compare");

	return ((struct iobject_vtable*)_inf_a->__vtable)->__compare_to((object)x, (object)y);
}
static bool object_equals(const_unknown x, const_unknown y) {
	_interface _inf_a = (_interface)__cast((unknown)x, IOBJECT_ID);
	_interface _inf_b = (_interface)__cast((unknown)y, IOBJECT_ID);

	/* first, two objects are both objects */
	if (_inf_a == NULL || _inf_b == NULL)
		rt_error("object_equals: at least one is not objects");

	/* first, two objects belongs to the same type */
	if (_inf_a->__vtable != _inf_b->__vtable)
		rt_error("object_equals: two objects are not the same type");

	/* third, the object has equals method */
	if (((struct iobject_vtable*)_inf_a->__vtable)->__equals == NULL)
		rt_error("object_equals: object does not support equals");

	return ((struct iobject_vtable*)_inf_a->__vtable)->__equals((object)x, (object)y);
}
static hashcode object_hashcode(const_unknown x) {
	_interface _inf = (_interface)__cast(x, IOBJECT_ID);
	
	if (_inf == NULL) 
		rt_error("object_hashcode: reference is not object");

	if (((struct iobject_vtable*)_inf->__vtable)->__hashcode == NULL)
		rt_error("object_hascode: does not have hash function");

	return ((struct iobject_vtable*)_inf->__vtable)->__hashcode((object)x);
}

unknown_traits object_traits = {
	object_destroy,
	object_clone,
	object_compare_to,
	object_equals,
	object_hashcode
};

inline bool iobject_distinguishable(const_object obj_a, const_object obj_b) {
	_interface _inf_a = (_interface)__cast((unknown)obj_a, IOBJECT_ID);
	_interface _inf_b = (_interface)__cast((unknown)obj_b, IOBJECT_ID);

	/* first, two objects are both objects */
	if (_inf_a == NULL || _inf_b == NULL)
		return false;

	/* first, two objects belongs to the same type */
	if (_inf_a->__vtable != _inf_b->__vtable)
		return false;

	/* third, the object has equals method */
	if (((struct iobject_vtable*)_inf_a->__vtable)->__equals == NULL)
		return false;

	return true;
}
inline bool iobject_comparable(const_object obj_a, const_object obj_b) {
	_interface _inf_a = (_interface)__cast((unknown)obj_a, IOBJECT_ID);
	_interface _inf_b = (_interface)__cast((unknown)obj_b, IOBJECT_ID);

	/* first, two objects are both objects */
	if (_inf_a == NULL || _inf_b == NULL)
		return false;

	/* first, two objects belongs to the same type */
	if (_inf_a->__vtable != _inf_b->__vtable)
		return false;

	/* third, the object has equals method */
	if (((struct iobject_vtable*)_inf_a->__vtable)->__compare_to == NULL)
		return false;

	return true;
}
inline bool iobject_hashable(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	return ((struct iobject_vtable*)_inf->__vtable)->__hashcode != NULL;
}

inline void iobject_destroy(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	((struct iobject_vtable*)_inf->__vtable)->__destroy(obj);
}
inline object iobject_clone(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	return ((struct iobject_vtable*)_inf->__vtable)->__clone(obj);
}
inline bool iobject_equals(const_object obj, const_object other) {
	_interface _inf = (_interface)__cast((unknown)obj, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	return ((struct iobject_vtable*)_inf->__vtable)->__equals(obj, other);
}
inline int iobject_compare_to(const_object obj, const_object other) {
	_interface _inf = (_interface)__cast((unknown)obj, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	return ((struct iobject_vtable*)_inf->__vtable)->__compare_to(obj, other);
}
inline hashcode iobject_hashcode(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IOBJECT_ID);
	dbg_assert(_inf != NULL);

	return ((struct iobject_vtable*)_inf->__vtable)->__hashcode(obj);
}
