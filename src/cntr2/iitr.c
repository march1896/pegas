#include <iitr.h>

inline void itr_destroy(iterator itr) {
	/* iterator object always inherit iiterator as the first interface */
	_interface intf = __fast_cast(itr, 0);
	dbg_assert(intf == __cast(itr, ITR_BAS_ID));

	((struct itr_base_vtable*)(intf->__vtable))->__destroy(itr);
}

inline iterator itr_clone(const_iterator itr) {
	_interface intf = __fast_cast(itr, 0);
	dbg_assert(intf == __cast(itr, ITR_BAS_ID));

	return ((struct itr_base_vtable*)(intf->__vtable))->__clone(itr);
}

inline bool itr_equals(const_iterator ia, const_iterator ib) {
	_interface intf = __fast_cast(ia, 0);
	dbg_assert(__cast(ia, ITR_BAS_ID) == __fast_cast(ia, 0));
	dbg_assert(__cast(ib, ITR_BAS_ID) == __fast_cast(ib, 0));

	return ((struct itr_base_vtable*)(intf->__vtable))->__equals(ia, ib);
}

inline const void* itr_get_ref(const_iterator itr) {
	_interface intf = __fast_cast((unknown)itr, 0);
	dbg_assert(intf == __cast((unknown)itr, ITR_REF_ID));

	return ((struct itr_readable_vtable*)(intf->__vtable))->__get_ref(itr);
}

inline void itr_set_ref(iterator itr, const void* __ref) {
	_interface intf = __fast_cast(itr, 0);
	dbg_assert(intf == __cast(itr, ITR_ACC_ID));

	((struct itr_accessible_vtable*)(intf->__vtable))->__set_ref(itr, __ref);
}

inline void itr_to_next(iterator itr) {
	_interface intf = __fast_cast(itr, 0);
	dbg_assert(intf == __cast(itr, ITR_FWD_ID));

	((struct itr_forward_vtable*)(intf->__vtable))->__to_next(itr);
}

inline void itr_to_prev(iterator itr) {
	_interface intf = __fast_cast(itr, 0);
	dbg_assert(intf == __cast(itr, ITR_BID_ID));

	((struct itr_bidirectional_vtable*)(intf->__vtable))->__to_prev(itr);
}

inline void itr_advance(iterator itr, int length) {
	_interface intf = __fast_cast(itr, 0);
	dbg_assert(intf == __cast(itr, ITR_RAC_ID));

	((struct itr_randomaccessible_vtable*)(intf->__vtable))->__advance(itr, length);
}

inline int  itr_distance(const_iterator from, const_iterator to) {
	_interface intf = __fast_cast((unknown)from, 0);
	dbg_assert(intf == __cast((unknown)from, ITR_RAC_ID));

	return ((struct itr_randomaccessible_vtable*)(intf->__vtable))->__distance(from, to);
}

/* TODO: not implemented yet */
/*
inline void iitr_destroy(_interface iitr);
inline bool iitr_equals(const_interface ia, const_interface ib);
inline void iitr_to_prev(_interface iitr);
inline void iitr_to_next(_interface iitr);
inline const void* iitr_get_ref(const_interface iitr);
inline void iitr_set_ref(_interface iitr, const void* __ref);
inline void iitr_advance(_interface iitr, int length);
inline int  iitr_distance(const_interface ifrom, const_interface ito);
*/
