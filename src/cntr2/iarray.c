#include <iarray.h>
#include <iitr.h>

inline void iarray_clear(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__clear(obj);
}
inline void iarray_foreach(object obj, pf_ref_process_v process, void* context) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__foreach(obj, process, context);
}
inline int  iarray_size(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__size(obj);
}
inline bool iarray_empty(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__empty(obj);
}
inline const_unknown iarray_front(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__front(obj);
}
inline const_unknown iarray_back(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__back(obj);
}
inline const_unknown iarray_at(const_object obj, int index) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__at(obj, index);
}
inline void iarray_add_front(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__add_front(obj, __ref);
}
inline void iarray_add_back(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__add_back(obj, __ref);
}
inline void iarray_remove_front(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__remove_front(obj);
}
inline void iarray_remove_back(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__remove_back(obj);
}
inline bool iarray_contains(const_object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__contains(obj, __ref);
}
inline bool iarray_remove(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__remove(obj, __ref);
}
inline iterator iarray_itr_create(const_object obj, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void iarray_itr_assign(const_object obj, iterator itr, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}
inline void iarray_itr_find(const_object obj, iterator itr, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__itr_find(obj, itr, __ref);
}
inline void iarray_itr_remove(object obj, iterator itr) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__itr_remove(obj, itr);
}
inline const_iterator iarray_itr_begin(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__itr_begin(obj);
}
inline const_iterator iarray_itr_end(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__itr_end(obj);
}
