#ifndef _INTERFACE_SET_H_
#define _INTERFACE_SET_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>

extern inline void     iset_destroy          (_interface ic);
extern inline void     iset_clear            (_interface ic);
extern inline void     iset_clear_v          (_interface ic, pf_ref_dispose_v dispose, void* context);
extern inline int      iset_size             (const_interface ic);
extern inline bool     iset_empty            (const_interface ic);
/* if some comp(__dup, __ref) == 0 is in the set, insert __ref, remove __dup and return __dup.
 * otherwise, if no comp(__any, __ref) == 0, just return NULL.
 * NOTE: if __ref(the address) is exactly in the set, __ref will be returned, so if you
 * dealloc(iset_insert(i, __ref)) without comparing the res to __ref, the inserted one maybe deleted. */
extern inline void*    iset_insert           (_interface ic, const void* __ref);
extern inline bool     iset_contains         (const_interface ic, const void* __ref);
/* return false if __ref is not in the set */
extern inline bool     iset_remove           (_interface ic, void* __ref);
extern inline void     iset_foreach          (_interface ic, pf_ref_visit_v process, void* context);

extern inline iterator iset_itr_create       (const_interface ic, itr_pos pos);
extern inline void     iset_itr_assign       (const_interface ic, /* out */iterator itr, itr_pos pos);
/* points to end if __ref is not in the set */
extern inline void     iset_itr_find         (const_interface ic, /* out */iterator itr, const void* __ref);
extern inline void*    iset_itr_remove       (_interface ic, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator iset_itr_begin  (const_interface ic);
extern inline const_iterator iset_itr_end    (const_interface ic);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_iset_destroy)    (object c);
typedef       void     (*pf_iset_clear)      (object c);
typedef       void     (*pf_iset_clear_v)    (object c, pf_ref_dispose_v dispose, void* context);
typedef       int      (*pf_iset_size)       (const_object c);
typedef       bool     (*pf_iset_empty)      (const_object c);
typedef       void*    (*pf_iset_insert)     (object c, const void* __ref);
typedef       bool     (*pf_iset_contains)   (const_object c, const void* __ref);
typedef       bool     (*pf_iset_remove)     (object c, void* __ref);

typedef       iterator (*pf_iset_itr_create) (const_object c, itr_pos pos);
typedef       void     (*pf_iset_itr_assign) (const_object c, iterator itr, itr_pos pos);
typedef       void     (*pf_iset_itr_find)   (const_object c, iterator itr, const void* __ref);
typedef       void*    (*pf_iset_itr_remove) (object c, iterator itr);
typedef const_iterator (*pf_iset_itr_begin)  (const_object c);
typedef const_iterator (*pf_iset_itr_end)    (const_object c);

struct iset_vtable {
	/* public */
	pf_iset_destroy     __destroy;
	pf_iset_clear       __clear;
	pf_iset_clear_v     __clear_v;
	pf_iset_size        __size;
	pf_iset_empty       __empty;
	pf_iset_insert      __insert;
	pf_iset_contains    __contains;
	pf_iset_remove      __remove;

	pf_iset_itr_create  __itr_create;
	pf_iset_itr_assign  __itr_assign;
	pf_iset_itr_find    __itr_find;
	pf_iset_itr_remove  __itr_remove;
	pf_iset_itr_begin   __itr_begin;
	pf_iset_itr_end     __itr_end;
};

/*******************************************************************************
 * imset declaration start 
 ******************************************************************************/
extern inline       void     imset_destroy    (_interface i);
extern inline       void     imset_clear      (_interface i);
/* NOTE: since we could add the same object to the same more than once, the dispose function may operates
 * on the same object more than once, you must take the risk on your own */
extern inline       void     imset_clear_v    (_interface i, pf_ref_dispose_v dispose, void* context);
extern inline       int      imset_size       (const_interface i);
extern inline       bool     imset_empty      (const_interface i);
extern inline       void     imset_insert     (_interface i, const void* __ref);
extern inline       bool     imset_contains   (const_interface i, const void* __ref);
/* return number of reference of __ref */
extern inline       int      imset_count      (const_interface i, const void* __ref);
/* return false if __ref is not in the set */
extern inline       bool     imset_remove     (_interface i, void* __ref);

extern inline       iterator imset_itr_create (const_interface i, itr_pos pos);
extern inline       void     imset_itr_assign (const_interface i, /* out */iterator itr, itr_pos pos);
/* find the minimum element which is greater or equal to __ref */
extern inline       void     imset_itr_find_lower(const_interface i, /* out */iterator itr, const void* __ref);
/* find the minimum element which is greater than __ref */
extern inline       void     imset_itr_find_upper(const_interface i, /* out */iterator itr, const void* __ref);
extern inline       void*    imset_itr_remove (_interface i, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator imset_itr_begin  (const_interface i);
extern inline const_iterator imset_itr_end    (const_interface i);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_imset_destroy)    (object o);
typedef       void     (*pf_imset_clear)      (object o);
/* TODO: how to handle the duplicated elements in the elements, the dispose often release the memory
 * back to the heap, how to handle the duplicated release calls on the same block of memory */
typedef       void     (*pf_imset_clear_v)    (object o, pf_ref_dispose_v dispose, void* context);
typedef       int      (*pf_imset_size)       (const_object o);
typedef       bool     (*pf_imset_empty)      (const_object o);
typedef       void     (*pf_imset_insert)     (object o, const void* __ref);
typedef       bool     (*pf_imset_contains)   (const_object o, const void* __ref);
typedef       int      (*pf_imset_count)      (const_object o, const void* __ref);
typedef       bool     (*pf_imset_remove)     (object o, void* __ref);

typedef       iterator (*pf_imset_itr_create) (const_object o, itr_pos pos);
typedef       void     (*pf_imset_itr_assign) (const_object o, iterator itr, itr_pos pos);
typedef       void     (*pf_imset_itr_find_lower)(const_object o, iterator itr, const void* __ref);
typedef       void     (*pf_imset_itr_find_upper)(const_object o, iterator itr, const void* __ref);
typedef       void*    (*pf_imset_itr_remove) (object o, iterator itr);
typedef const_iterator (*pf_imset_itr_begin)  (const_object o);
typedef const_iterator (*pf_imset_itr_end)    (const_object o);

struct imset_vtable {
	/* public */
	pf_imset_destroy        __destroy;
	pf_imset_clear          __clear;
	pf_imset_clear_v        __clear_v;
	pf_imset_size           __size;
	pf_imset_empty          __empty;
	pf_imset_insert         __insert;
	pf_imset_contains       __contains;
	pf_imset_count          __count;
	pf_imset_remove         __remove;

	pf_imset_itr_create     __itr_create;
	pf_imset_itr_assign     __itr_assign;
	pf_imset_itr_find_lower __itr_find_lower;
	pf_imset_itr_find_upper __itr_find_upper;
	pf_imset_itr_remove     __itr_remove;
	pf_imset_itr_begin      __itr_begin;
	pf_imset_itr_end        __itr_end;
};

#endif /* _INTERFACE_SET_H_ */
