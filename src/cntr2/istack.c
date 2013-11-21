#include <istack.h>
#include <iitr.h>

inline void istack_clear(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__clear(obj);
}

inline void istack_foreach(Object* obj, pf_ref_process_v process, void* context) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__foreach(obj, process, context);
}

inline int istack_size(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__size(obj);
}

inline bool istack_empty(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__empty(obj);
}

inline const unknown* istack_top(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__top(obj);
}

inline void istack_push(Object* obj, const unknown* __ref) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__push(obj, __ref);
}

inline void istack_pop(Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)(_inf->__vtable))->__pop(obj);
}
inline iterator istack_itr_create(const Object* obj, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)_inf->__vtable)->__itr_create(obj, pos);
}
inline void istack_itr_assign(const Object* obj, iterator itr, itr_pos pos) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	((struct istack_vtable*)_inf->__vtable)->__itr_assign(obj, itr, pos);
}
inline const_iterator istack_itr_begin(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__itr_begin(obj);
}

inline const_iterator istack_itr_end(const Object* obj) {
	_interface* _inf = (_interface*)__cast(obj, ISTACK_ID);
	dbg_assert(_inf != NULL);

	return ((struct istack_vtable*)(_inf->__vtable))->__itr_end(obj);
}
