#include <istack.h>

inline void istack_destroy(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__destroy(obj);
}

inline void istack_clear(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__clear(obj);
}

inline void istack_foreach(object obj, pf_ref_process_v process, void* context) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__foreach(obj, process, context);
}

inline int istack_size(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__size(obj);
}

inline bool istack_empty(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__empty(obj);
}

inline const_unknown istack_top(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__top(obj);
}

inline void istack_push(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__push(obj, __ref);
}

inline void istack_pop(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__pop(obj);
}
inline iterator istack_itr_create(const_object obj, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void istack_itr_assign(const_object obj, iterator itr, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}
inline const_iterator istack_itr_begin(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator istack_itr_end(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__itr_end(obj);
}
