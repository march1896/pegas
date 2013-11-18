#ifndef _INTERFACE_SET_H_
#define _INTERFACE_SET_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>

extern inline void     iset_clear            (object obj);
extern inline int      iset_size             (const_object obj);
extern inline bool     iset_empty            (const_object obj);
/* if __ref is in the set, do nothing, else insert it */
extern inline void     iset_insert           (object obj, const_unknown __ref);
/* if __ref is in the set, replace the reference to the new one, else insert it */
/* NOTE: iset_replace does exactly the same thing as iset_insert for raw types */
extern inline void     iset_replace          (object obj, const_unknown __ref);
extern inline bool     iset_contains         (const_object obj, const_unknown __ref);
/* return false if __ref is not in the set */
extern inline bool     iset_remove           (object obj, const_unknown __ref);
extern inline void     iset_foreach          (object obj, pf_ref_visit_v process, void* context);

extern inline iterator iset_itr_create       (const_object obj, itr_pos pos);
extern inline void     iset_itr_assign       (const_object obj, /* out */iterator itr, itr_pos pos);
/* points to end if __ref is not in the set */
extern inline void     iset_itr_find         (const_object obj, /* out */iterator itr, const_unknown __ref);
extern inline void     iset_itr_remove       (object obj, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator iset_itr_begin  (const_object obj);
extern inline const_iterator iset_itr_end    (const_object obj);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_iset_clear)      (object obj);
typedef       int      (*pf_iset_size)       (const_object obj);
typedef       bool     (*pf_iset_empty)      (const_object obj);
typedef       void     (*pf_iset_insert)     (object obj, const_unknown __ref);
typedef       void     (*pf_iset_replace)    (object obj, const_unknown __ref);
typedef       bool     (*pf_iset_contains)   (const_object obj, const_unknown __ref);
typedef       bool     (*pf_iset_remove)     (object obj, const_unknown __ref);

typedef       iterator (*pf_iset_itr_create) (const_object obj, itr_pos pos);
typedef       void     (*pf_iset_itr_assign) (const_object obj, iterator itr, itr_pos pos);
typedef       void     (*pf_iset_itr_find)   (const_object obj, iterator itr, const void* __ref);
typedef       void     (*pf_iset_itr_remove) (object obj, iterator itr);
typedef const_iterator (*pf_iset_itr_begin)  (const_object obj);
typedef const_iterator (*pf_iset_itr_end)    (const_object obj);

struct iset_vtable {
	/* public */
	pf_iset_clear       __clear;
	pf_iset_size        __size;
	pf_iset_empty       __empty;
	pf_iset_insert      __insert;
	pf_iset_insert      __update;
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
extern inline       void     imset_clear      (object obj);
extern inline       int      imset_size       (const_object obj);
extern inline       bool     imset_empty      (const_object obj);
extern inline       void     imset_insert     (object obj, const_unknown __ref);
extern inline       bool     imset_contains   (const_object obj, const_unknown __ref);
/* return number of reference of __ref */
extern inline       int      imset_count      (const_object obj, const_unknown __ref);
/* return the number of removed elements in the multiple set */
extern inline       int      imset_remove     (object obj, const_unknown __ref);

extern inline       iterator imset_itr_create (const_object obj, itr_pos pos);
extern inline       void     imset_itr_assign (const_object obj, /* out */iterator itr, itr_pos pos);
/* find the minimum element which is greater or equal to __ref */
extern inline       void     imset_itr_find_lower(const_object obj, /* out */iterator itr, const_unknown __ref);
/* find the minimum element which is greater than __ref */
extern inline       void     imset_itr_find_upper(const_object obj, /* out */iterator itr, const_unknown __ref);
extern inline       void     imset_itr_remove (object obj, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator imset_itr_begin  (const_object obj);
extern inline const_iterator imset_itr_end    (const_object obj);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_imset_clear)      (object obj);
typedef       int      (*pf_imset_size)       (const_object obj);
typedef       bool     (*pf_imset_empty)      (const_object obj);
typedef       void     (*pf_imset_insert)     (object obj, const_unknown __ref);
typedef       bool     (*pf_imset_contains)   (const_object obj, const_unknown __ref);
typedef       int      (*pf_imset_count)      (const_object obj, const_unknown __ref);
typedef       int      (*pf_imset_remove)     (object obj, const_unknown __ref);

typedef       iterator (*pf_imset_itr_create) (const_object obj, itr_pos pos);
typedef       void     (*pf_imset_itr_assign) (const_object obj, iterator itr, itr_pos pos);
typedef       void     (*pf_imset_itr_find_lower)(const_object obj, iterator itr, const_unknown __ref);
typedef       void     (*pf_imset_itr_find_upper)(const_object obj, iterator itr, const_unknown __ref);
typedef       void     (*pf_imset_itr_remove) (object obj, iterator itr);
typedef const_iterator (*pf_imset_itr_begin)  (const_object obj);
typedef const_iterator (*pf_imset_itr_end)    (const_object obj);

struct imset_vtable {
	/* public */
	pf_imset_clear          __clear;
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
