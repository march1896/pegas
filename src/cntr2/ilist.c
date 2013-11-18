#include <ilist.h>

inline void ilist_clear(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__clear(obj);
}
inline void ilist_foreach(object obj, pf_ref_process_v process, void* context) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__foreach(obj, process, context);
}
inline int  ilist_size(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__size(obj);
}
inline bool ilist_empty(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__empty(obj);
}
inline const_unknown ilist_front(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__front(obj);
}
inline const_unknown ilist_back(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__back(obj);
}
inline void ilist_add_front(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__add_front(obj, __ref);
}
inline void ilist_add_back(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__add_back(obj, __ref);
}
inline void ilist_remove_front(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__remove_front(obj);
}
inline void ilist_remove_back(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__remove_back(obj);
}
inline bool ilist_contains(const_object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__contains(obj, __ref);
}
inline bool ilist_remove(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__remove(obj, __ref);
}
inline iterator ilist_itr_create(const_object obj, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void ilist_itr_assign(const_object obj, iterator itr, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}
inline void ilist_itr_find(const_object obj, iterator itr, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__itr_find(obj, itr, __ref);
}
inline void ilist_itr_remove(object obj, iterator itr) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__itr_remove(obj, itr);
}
inline void ilist_itr_insert_before(object obj, iterator itr, const_unknown n_ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__itr_insert_before(obj, itr, n_ref);
}
inline void ilist_itr_insert_after(object obj, iterator itr, const_unknown n_ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	((struct ilist_vtable*)_inf->__vtable)->__itr_insert_after(obj, itr, n_ref);
}
inline const_iterator ilist_itr_begin(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__itr_begin(obj);
}
inline const_iterator ilist_itr_end(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ILIST_ID);
	dbg_assert(_inf != NULL);

	return ((struct ilist_vtable*)_inf->__vtable)->__itr_end(obj);
}
