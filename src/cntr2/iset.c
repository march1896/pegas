#include <iset.h>

/*******************************************************************************
 * iset implementation start 
 ******************************************************************************/

inline void iset_clear(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__clear(obj);
}

inline void iset_clear_v(object obj, pf_ref_dispose_v dispose, void* context) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__clear_v(obj, dispose, context);
}

inline int iset_size(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__size(obj);
}

inline bool iset_empty(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__empty(obj);
}

inline void* iset_insert(object obj, const void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__insert(obj, __ref);
}

inline bool iset_contains(const_object obj, const void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__contains(obj, __ref);
}

inline bool iset_remove(object obj, void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__remove(obj, __ref);
}
inline iterator iset_itr_create(const_object obj, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__itr_create(obj, pos);
}
inline void iset_itr_assign(const_object obj, iterator itr, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__itr_assign(obj, itr, pos);
}
inline void iset_itr_find(const_object obj, iterator itr, const void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__itr_find(obj, itr, __ref);
}
inline void* iset_itr_remove(object obj, iterator itr) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__itr_remove(obj, itr);
}
inline const_iterator iset_itr_begin(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator iset_itr_end(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__itr_end(obj);
}

/*******************************************************************************
 * imset implementation start 
 ******************************************************************************/

inline void imset_clear(object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__clear(obj);
}

inline void imset_clear_v(object obj, pf_ref_dispose_v dispose, void* context) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__clear_v(obj, dispose, context);
}

inline int imset_size(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__size(obj);
}

inline bool imset_empty(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__empty(obj);
}

inline void imset_insert(object obj, const void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__insert(obj, __ref);
}

inline bool imset_contains(const_object obj, const void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__contains(obj, __ref);
}

inline int imset_count(const_object obj, const void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__count(obj, __ref);
}

inline bool imset_remove(object obj, void* __ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__remove(obj, __ref);
}
inline iterator imset_itr_create(const_object obj, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__itr_create(obj, pos);
}
inline void imset_itr_assign(const_object obj, iterator itr, itr_pos pos) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__itr_assign(obj, itr, pos);
}
inline void imset_itr_find_lower(const_object obj, iterator itr, const void* ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__itr_find_lower(obj, itr, ref);
}
inline void imset_itr_find_upper(const_object obj, iterator itr, const void* ref) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__itr_find_upper(obj, itr, ref);
}
inline void* imset_itr_remove(object obj, iterator itr) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__itr_remove(obj, itr);
}
inline const_iterator imset_itr_begin(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator imset_itr_end(const_object obj) {
	_interface _inf = (_interface)__cast((unknown)obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__itr_end(obj);
}
