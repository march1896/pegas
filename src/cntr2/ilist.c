#include <ilist.h>

inline void ilist_destroy(_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__destroy(o);
}
inline void ilist_clear(_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__clear(o);
}
inline void ilist_foreach(_interface ilist, pf_ref_process_v process, void* context) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__foreach(o, process, context);
}
inline int  ilist_size(const_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)ilist->__vtable)->__size(o);
}
inline bool ilist_empty(const_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)(ilist->__vtable))->__empty(o);
}
inline const_unknown ilist_front(const_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)(ilist->__vtable))->__front(o);
}
inline const_unknown ilist_back(const_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)(ilist->__vtable))->__back(o);
}
inline void ilist_add_front(_interface ilist, const_unknown __ref) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__add_front(o, __ref);
}
inline void ilist_add_back(_interface ilist, const_unknown __ref) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__add_back(o, __ref);
}
inline void ilist_remove_front(_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__remove_front(o);
}
inline void ilist_remove_back(_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__remove_back(o);
}
inline bool ilist_contains(const_interface ilist, const_unknown __ref) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)ilist->__vtable)->__contains(o, __ref);
}
inline bool ilist_remove(_interface ilist, const_unknown __ref) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)ilist->__vtable)->__remove(o, __ref);
}
inline iterator ilist_itr_create(const_interface ilist, itr_pos pos) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)ilist->__vtable)->__itr_create(o, pos);
}
inline void ilist_itr_assign(const_interface ilist, iterator itr, itr_pos pos) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__itr_assign(o, itr, pos);
}
inline void ilist_itr_find(const_interface ilist, iterator itr, const_unknown __ref) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__itr_find(o, itr, __ref);
}
inline void ilist_itr_remove(_interface ilist, iterator itr) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__itr_remove(o, itr);
}
inline void ilist_itr_insert_before(_interface ilist, iterator itr, const_unknown n_ref) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__itr_insert_before(o, itr, n_ref);
}
inline void ilist_itr_insert_after(_interface ilist, iterator itr, const_unknown n_ref) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	((struct ilist_vtable*)ilist->__vtable)->__itr_insert_after(o, itr, n_ref);
}
inline const_iterator ilist_itr_begin(const_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)ilist->__vtable)->__itr_begin(o);
}
inline const_iterator ilist_itr_end(const_interface ilist) {
	object o = __object_from_interface(ilist);
	dbg_assert(__cast(o, ILIST_ID) == ilist);

	return ((struct ilist_vtable*)ilist->__vtable)->__itr_end(o);
}
