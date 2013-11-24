#include <cntr2/iarray.h>
#include <cntr2/iitr.h>

inline void iarray_clear(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__clear(obj);
}
inline void iarray_foreach(Object* obj, pf_ref_process_v process, void* context) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__foreach(obj, process, context);
}
inline int  iarray_size(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__size(obj);
}
inline bool iarray_empty(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__empty(obj);
}
inline const unknown* iarray_front(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__front(obj);
}
inline const unknown* iarray_back(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__back(obj);
}
inline const unknown* iarray_at(const Object* obj, int index) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__at(obj, index);
}
inline void iarray_add_front(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__add_front(obj, __ref);
}
inline void iarray_add_back(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__add_back(obj, __ref);
}
inline void iarray_remove_front(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__remove_front(obj);
}
inline void iarray_remove_back(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__remove_back(obj);
}
inline bool iarray_contains(const Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__contains(obj, __ref);
}
inline bool iarray_remove(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__remove(obj, __ref);
}
inline iterator iarray_itr_create(const Object* obj, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void iarray_itr_assign(const Object* obj, iterator itr, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}
inline void iarray_itr_find(const Object* obj, iterator itr, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__itr_find(obj, itr, __ref);
}
inline void iarray_itr_remove(Object* obj, iterator itr) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	((struct iarray_vtable*)_inf->__vtable)->__itr_remove(obj, itr);
}
inline const_iterator iarray_itr_begin(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__itr_begin(obj);
}
inline const_iterator iarray_itr_end(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, IARRAY_ID);
	dbg_assert(_inf != NULL);

	return ((struct iarray_vtable*)_inf->__vtable)->__itr_end(obj);
}
