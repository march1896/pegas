#include <istack.h>

inline void istack_destroy(_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	((struct istack_vtable*)(iq->__vtable))->__destroy(o);
}

inline void istack_clear(_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	((struct istack_vtable*)(iq->__vtable))->__clear(o);
}

inline void istack_foreach(_interface iq, pf_ref_process_v process, void* context) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	((struct istack_vtable*)(iq->__vtable))->__foreach(o, process, context);
}

inline int istack_size(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	return ((struct istack_vtable*)(iq->__vtable))->__size(o);
}

inline bool istack_empty(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	return ((struct istack_vtable*)(iq->__vtable))->__empty(o);
}

inline const_unknown istack_top(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	return ((struct istack_vtable*)(iq->__vtable))->__top(o);
}

inline void istack_push(_interface iq, const_unknown __ref) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	((struct istack_vtable*)(iq->__vtable))->__push(o, __ref);
}

inline void istack_pop(_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	((struct istack_vtable*)(iq->__vtable))->__pop(o);
}
inline iterator istack_itr_create(const_interface iq, itr_pos pos) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	return ((struct istack_vtable*)iq->__vtable)->__itr_create(o, pos);
}
inline void istack_itr_assign(const_interface iq, iterator itr, itr_pos pos) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	((struct istack_vtable*)iq->__vtable)->__itr_assign(o, itr, pos);
}
inline const_iterator istack_itr_begin(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	return ((struct istack_vtable*)(iq->__vtable))->__itr_begin(o);
}

inline const_iterator istack_itr_end(const_interface iq) {
	object o = __object_from_interface(iq);
	dbg_assert(__cast(o, ISTACK_ID) == iq);

	return ((struct istack_vtable*)(iq->__vtable))->__itr_end(o);
}
