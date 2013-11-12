#include <iqueue.h>

inline void iqueue_destroy(_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	((struct iqueue_vtable*)(iq->__vtable))->__destroy(o);
}

inline void iqueue_clear(_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	((struct iqueue_vtable*)(iq->__vtable))->__clear(o);
}

inline void iqueue_foreach(_interface iq, pf_ref_process_v process, void* context) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	((struct iqueue_vtable*)(iq->__vtable))->__foreach(o, process, context);
}

inline int  iqueue_size(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	return ((struct iqueue_vtable*)(iq->__vtable))->__size(o);
}

inline bool iqueue_empty(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	return ((struct iqueue_vtable*)(iq->__vtable))->__empty(o);
}

inline const_unknown iqueue_front(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	return ((struct iqueue_vtable*)(iq->__vtable))->__front(o);
}

inline const_unknown iqueue_back(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	return ((struct iqueue_vtable*)(iq->__vtable))->__back(o);
}

inline void iqueue_push(_interface iq, const_unknown __ref) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	((struct iqueue_vtable*)(iq->__vtable))->__push(o, __ref);
}

inline void iqueue_pop(_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	((struct iqueue_vtable*)(iq->__vtable))->__pop(o);
}
inline iterator iqueue_itr_create(const_interface iq, itr_pos pos) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	return ((struct iqueue_vtable*)iq->__vtable)->__itr_create(o, pos);
}
inline void iqueue_itr_assign(const_interface iq, iterator itr, itr_pos pos) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	((struct iqueue_vtable*)iq->__vtable)->__itr_assign(o, itr, pos);
}

inline const_iterator iqueue_itr_begin(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	return ((struct iqueue_vtable*)(iq->__vtable))->__itr_begin(o);
}

inline const_iterator iqueue_itr_end(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, IQUEUE_ID) == iq);

	return ((struct iqueue_vtable*)(iq->__vtable))->__itr_end(o);
}
