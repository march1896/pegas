#include <iobject.h>

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
