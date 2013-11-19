#include <iqueue.h>
#include <iitr.h>

inline void iqueue_clear(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	((struct iqueue_vtable*)(_inf->__vtable))->__clear(obj);
}

inline void iqueue_foreach(object obj, pf_ref_process_v process, void* context) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	((struct iqueue_vtable*)(_inf->__vtable))->__foreach(obj, process, context);
}

inline int  iqueue_size(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	return ((struct iqueue_vtable*)(_inf->__vtable))->__size(obj);
}

inline bool iqueue_empty(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	return ((struct iqueue_vtable*)(_inf->__vtable))->__empty(obj);
}

inline const_unknown iqueue_front(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	return ((struct iqueue_vtable*)(_inf->__vtable))->__front(obj);
}

inline const_unknown iqueue_back(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	return ((struct iqueue_vtable*)(_inf->__vtable))->__back(obj);
}

inline void iqueue_push(object obj, const_unknown __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	((struct iqueue_vtable*)(_inf->__vtable))->__push(obj, __ref);
}

inline void iqueue_pop(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	((struct iqueue_vtable*)(_inf->__vtable))->__pop(obj);
}
inline iterator iqueue_itr_create(const_object obj, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	return ((struct iqueue_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void iqueue_itr_assign(const_object obj, iterator itr, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	((struct iqueue_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}

inline const_iterator iqueue_itr_begin(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	return ((struct iqueue_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator iqueue_itr_end(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IQUEUE_ID);
	dbg_assert(_inf != NULL);

	return ((struct iqueue_vtable*)(_inf->__vtable))->__itr_end(obj);
}
