#include <cntr2/imap.h>
#include <cntr2/iitr.h>

/*******************************************************************************
 * imap implementation start 
 ******************************************************************************/

inline void imap_clear(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	((struct imap_vtable*)(_inf->__vtable))->__clear(obj);
}
inline int imap_size(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct imap_vtable*)(_inf->__vtable))->__size(obj);
}
inline bool imap_empty(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct imap_vtable*)(_inf->__vtable))->__empty(obj);
}
inline void imap_insert(Object* obj, const unknown* key, const unknown* value) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	((struct imap_vtable*)(_inf->__vtable))->__insert(obj, key, value);
}
inline bool imap_contains(const Object* obj, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct imap_vtable*)(_inf->__vtable))->__contains(obj, key);
}
inline const unknown* imap_findbykey(const Object* obj, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct imap_vtable*)(_inf->__vtable))->__findbykey(obj, key);
}
inline void imap_remove(Object* obj, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	((struct imap_vtable*)(_inf->__vtable))->__remove(obj, key);
}
inline iterator imap_itr_create(const Object* obj, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct imap_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void imap_itr_assign(const Object* obj, iterator itr, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	((struct imap_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}
inline void imap_itr_find(const Object* obj, iterator itr, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	((struct imap_vtable*)(_inf->__vtable))->__itr_find(obj, itr, key);
}
inline void imap_itr_remove(Object* obj, iterator itr) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	((struct imap_vtable*)(_inf->__vtable))->__itr_remove(obj, itr);
}
inline const_iterator imap_itr_begin(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct imap_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator imap_itr_end(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct imap_vtable*)(_inf->__vtable))->__itr_end(obj);
}

/*******************************************************************************
 * immap implementation start 
 ******************************************************************************/

inline void immap_clear(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	((struct immap_vtable*)(_inf->__vtable))->__clear(obj);
}
inline int immap_size(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)(_inf->__vtable))->__size(obj);
}
inline bool immap_empty(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)(_inf->__vtable))->__empty(obj);
}
inline void immap_insert(Object* obj, const unknown* key, const unknown* value) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	((struct immap_vtable*)(_inf->__vtable))->__insert(obj, key, value);
}
inline bool immap_contains(const Object* obj, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)(_inf->__vtable))->__contains(obj, key);
}
inline int immap_count(const Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)(_inf->__vtable))->__count(obj, __ref);
}
inline bool immap_remove(Object* obj, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)(_inf->__vtable))->__remove(obj, key);
}
inline iterator immap_itr_create(const Object* obj, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void immap_itr_assign(const Object* obj, iterator itr, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	((struct immap_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}
inline void immap_itr_find_lower(const Object* obj, iterator itr, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	((struct immap_vtable*)(_inf->__vtable))->__itr_find_lower(obj, itr, key);
}
inline void immap_itr_find_upper(const Object* obj, iterator itr, const unknown* key) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	((struct immap_vtable*)(_inf->__vtable))->__itr_find_upper(obj, itr, key);
}
inline void immap_itr_remove(Object* obj, iterator itr) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	((struct immap_vtable*)(_inf->__vtable))->__itr_remove(obj, itr);
}
inline const_iterator immap_itr_begin(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator immap_itr_end(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IMMAP_ID);
	dbg_assert(_inf != NULL);

	return ((struct immap_vtable*)(_inf->__vtable))->__itr_end(obj);
}
