#include <cntr2/iset.h>
#include <cntr2/iitr.h>

/*******************************************************************************
 * iset implementation start 
 ******************************************************************************/

inline void iset_clear(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__clear(obj);
}

inline int iset_size(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__size(obj);
}

inline bool iset_empty(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__empty(obj);
}

inline void iset_insert(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__insert(obj, __ref);
}

inline void iset_replace(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__insert(obj, __ref);
}

inline bool iset_contains(const Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__contains(obj, __ref);
}

inline bool iset_remove(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__remove(obj, __ref);
}
inline iterator iset_itr_create(const Object* obj, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__itr_create(obj, pos);
}
inline void iset_itr_assign(const Object* obj, iterator itr, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__itr_assign(obj, itr, pos);
}
inline void iset_itr_find(const Object* obj, iterator itr, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__itr_find(obj, itr, __ref);
}
inline void iset_itr_remove(Object* obj, iterator itr) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	((struct iset_vtable*)(_inf->__vtable))->__itr_remove(obj, itr);
}
inline const_iterator iset_itr_begin(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator iset_itr_end(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISET_ID);
	dbg_assert(_inf != NULL);

	return ((struct iset_vtable*)(_inf->__vtable))->__itr_end(obj);
}

/*******************************************************************************
 * imset implementation start 
 ******************************************************************************/

inline void imset_clear(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__clear(obj);
}

inline int imset_size(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__size(obj);
}

inline bool imset_empty(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__empty(obj);
}

inline void imset_insert(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__insert(obj, __ref);
}

inline bool imset_contains(const Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__contains(obj, __ref);
}

inline int imset_count(const Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__count(obj, __ref);
}

inline int imset_remove(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__remove(obj, __ref);
}
inline iterator imset_itr_create(const Object* obj, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__itr_create(obj, pos);
}
inline void imset_itr_assign(const Object* obj, iterator itr, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__itr_assign(obj, itr, pos);
}
inline void imset_itr_find_lower(const Object* obj, iterator itr, const unknown* ref) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__itr_find_lower(obj, itr, ref);
}
inline void imset_itr_find_upper(const Object* obj, iterator itr, const unknown* ref) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__itr_find_upper(obj, itr, ref);
}
inline void imset_itr_remove(Object* obj, iterator itr) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	((struct imset_vtable*)(_inf->__vtable))->__itr_remove(obj, itr);
}
inline const_iterator imset_itr_begin(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator imset_itr_end(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMSET_ID);
	dbg_assert(_inf != NULL);

	return ((struct imset_vtable*)(_inf->__vtable))->__itr_end(obj);
}
