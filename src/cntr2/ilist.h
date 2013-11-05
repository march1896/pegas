#ifndef _INTERFACE_LIST_H_
#define _INTERFACE_LIST_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>

extern inline       void     ilist_destroy         (iobject* ilist);
extern inline       void     ilist_clear           (iobject* ilist);
extern inline       void     ilist_foreach         (iobject* ilist, pf_ref_process_v process, void* context);
extern inline       int      ilist_size            (const iobject* ilist);
extern inline       void     ilist_add_front       (iobject* ilist, const void* n_ref);
extern inline       bool     ilist_empty           (const iobject* ilist);
extern inline const void*    ilist_front           (const iobject* ilist);
extern inline const void*    ilist_back            (const iobject* ilist);
extern inline       void     ilist_add_back        (iobject* ilist, const void* n_ref);
extern inline       void*    ilist_remove_front    (iobject* ilist);
extern inline       void*    ilist_remove_back     (iobject* ilist);
extern inline       bool     ilist_contains        (const iobject* ilist, const void* __ref);
extern inline       bool     ilist_remove          (iobject* ilist, void* __ref);

/* return the begin iterator of the container, this iterator is constant, 
 * you could only use it for comparison, dereferencing.
 * you can not move it or set reference on it. */
extern inline const_iterator ilist_itr_begin       (const iobject* ilist);
extern inline const_iterator ilist_itr_end         (const iobject* ilist);
extern inline       iterator ilist_itr_create      (const iobject* ilist, itr_pos pos);
extern inline       void     ilist_itr_assign      (const iobject* ilist, iterator itr, itr_pos pos);
extern inline       void     ilist_itr_find        (const iobject* ilist, iterator itr, void* __ref);
extern inline       void*    ilist_itr_remove      (iobject* ilist, iterator itr);
extern inline       void     ilist_itr_insert_before (iobject* ilist, iterator itr, void* n_ref);
extern inline       void     ilist_itr_insert_after  (iobject* ilist, iterator itr, void* n_ref);

/*
{
	iterator itr = ilist_itr_create(list, itr_begin);
	const_iterator end = ilist_itr_end(ilist);
	for (; !itr_equals(itr, end); itr_to_next(itr)) {
		// do something on itr
	}
	itr_destroy(itr);
}
*/

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_ilist_destroy)      (object* olist);
typedef       void     (*pf_ilist_clear)        (object* olist);
typedef       void     (*pf_ilist_foreach)      (object* olist, pf_ref_process_v process, void* context);
typedef       int      (*pf_ilist_size)         (const object* olist);
typedef       bool     (*pf_ilist_empty)        (const object* olist);
typedef const void*    (*pf_ilist_front)        (const object* olist);
typedef const void*    (*pf_ilist_back)         (const object* olist);
typedef       void     (*pf_ilist_add_front)    (object* olist, const void* n_ref);
typedef       void     (*pf_ilist_add_back)     (object* olist, const void* n_ref);
typedef       void*    (*pf_ilist_remove_front) (object* olist);
typedef       void*    (*pf_ilist_remove_back)  (object* olist);
typedef       bool     (*pf_ilist_contains)     (const object* olist, const void* __ref);
typedef       bool     (*pf_ilist_remove)       (object* olist, void* __ref);

typedef const_iterator (*pf_ilist_itr_begin)    (const object* olist);
typedef const_iterator (*pf_ilist_itr_end)      (const object* olist);
typedef       iterator (*pf_ilist_itr_create)   (const object* ilist, itr_pos pos);
typedef       void     (*pf_ilist_itr_assign)   (const object* ilist, /*out*/iterator itr, itr_pos pos);
typedef       void     (*pf_ilist_itr_find)     (const object* olist, /*out*/iterator itr, void* __ref);
typedef       void*    (*pf_ilist_itr_remove)   (object* olist, iterator itr);
typedef       void     (*pf_ilist_itr_insert_before)(object* olist, iterator itr, void* n_ref);
typedef       void     (*pf_ilist_itr_insert_after) (object* olist, iterator itr, void* n_ref);


struct ilist_vtable {
	/* public */
	pf_ilist_destroy        __destroy;
	pf_ilist_clear          __clear;
	pf_ilist_foreach        __foreach;
	pf_ilist_size           __size;
	pf_ilist_empty          __empty;
	pf_ilist_front          __front;
	pf_ilist_back           __back;
	pf_ilist_add_front      __add_front;
	pf_ilist_add_back       __add_back;
	pf_ilist_remove_front   __remove_front;
	pf_ilist_remove_back    __remove_back;
	pf_ilist_contains       __contains;
	pf_ilist_remove         __remove;

	pf_ilist_itr_begin      __itr_begin;
	pf_ilist_itr_end        __itr_end;
	pf_ilist_itr_create     __itr_create;
	pf_ilist_itr_assign     __itr_assign;
	pf_ilist_itr_find       __itr_find;
	pf_ilist_itr_remove     __itr_remove;
	pf_ilist_itr_insert_before  __itr_insert_before;
	pf_ilist_itr_insert_after   __itr_insert_after;
};

#endif /* _INTERFACE_LIST_H_ */
