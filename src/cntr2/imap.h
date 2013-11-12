#ifndef _INTERFACE_MAP_H_
#define _INTERFACE_MAP_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>

typedef struct map_pair_t {
	const void* key;
	void*       value;
} map_pair;

extern inline void     imap_destroy          (_interface ic);
extern inline void     imap_clear            (_interface ic);
extern inline void     imap_clear_v          (_interface ic, pf_ref_dispose_v dispose, void* context);
extern inline int      imap_size             (const_interface ic);
extern inline bool     imap_empty            (const_interface ic);
/* if <key, old_value> pair in the map, the old_value will be updated, and the old_value 
 * will be returned, if not, return NULL. */
extern inline void*    imap_insert           (_interface ic, const void* key, void* value);
extern inline bool     imap_contains         (const_interface ic, const void* key);
/* return NULL if the key is not in the map */
extern inline void*    imap_findbykey        (const_interface ic, const void* key);
/* return NULL if key is not in the map, or the <key, value> pair will be removed from the map */
extern inline void*    imap_remove           (_interface ic, void* key);

extern inline iterator imap_itr_create       (const_interface ic, itr_pos pos);
extern inline void     imap_itr_assign       (const_interface ic, /* out */iterator itr, itr_pos pos);
/* points to end if key is not in the map */
extern inline void     imap_itr_find         (const_interface ic, /* out */iterator itr, void* key);
extern inline void*    imap_itr_remove       (_interface ic, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator imap_itr_begin  (const_interface ic);
extern inline const_iterator imap_itr_end    (const_interface ic);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_imap_destroy)    (object c);
typedef       void     (*pf_imap_clear)      (object c);
typedef       void     (*pf_imap_clear_v)    (object c, pf_ref_dispose_v dispose, void* context);
typedef       int      (*pf_imap_size)       (const_object c);
typedef       bool     (*pf_imap_empty)      (const_object c);
typedef       void*    (*pf_imap_insert)     (object c, const void* key, void* value);
typedef       bool     (*pf_imap_contains)   (const_object c, const void* key);
typedef       void*    (*pf_imap_findbykey)  (const_object c, const void* key);
typedef       void*    (*pf_imap_remove)     (object c, void* key);

typedef       iterator (*pf_imap_itr_create) (const_object c, itr_pos pos);
typedef       void     (*pf_imap_itr_assign) (const_object c, iterator itr, itr_pos pos);
typedef       void     (*pf_imap_itr_find)   (const_object c, iterator itr, void* key);
typedef       void*    (*pf_imap_itr_remove) (object c, iterator itr);
typedef const_iterator (*pf_imap_itr_begin)  (const_object c);
typedef const_iterator (*pf_imap_itr_end)    (const_object c);

struct imap_vtable {
	pf_imap_destroy     __destroy;
	pf_imap_clear       __clear;
	pf_imap_size        __size;
	pf_imap_empty       __empty;
	pf_imap_insert      __insert;
	pf_imap_contains    __contains;
	pf_imap_findbykey   __findbykey;
	pf_imap_remove      __remove;

	pf_imap_itr_create  __itr_create;
	pf_imap_itr_assign  __itr_assign;
	pf_imap_itr_find    __itr_find;
	pf_imap_itr_remove  __itr_remove;
	pf_imap_itr_begin   __itr_begin;
	pf_imap_itr_end     __itr_end;
};

/*******************************************************************************
 * immap declaration start 
 ******************************************************************************/
extern inline void     immap_destroy    (_interface i);
extern inline void     immap_clear      (_interface i);
extern inline void     immap_clear_v    (_interface i, pf_ref_dispose_v dispose, void* context);
extern inline int      immap_size       (const_interface i);
extern inline bool     immap_empty      (const_interface i);
extern inline void     immap_insert     (_interface i, const void* key, void* value);
extern inline bool     immap_contains   (const_interface i, const void* key);
/* return number of reference of key */
extern inline int      immap_count      (const_interface i, const void* key);
extern inline bool     immap_remove     (_interface i, void* key);

extern inline iterator immap_itr_create (const_interface i, itr_pos pos);
extern inline void     immap_itr_assign (const_interface i, /* out */iterator itr, itr_pos pos);
/* find the minimum element which is greater or equal to key */
extern inline void     immap_itr_find_lower(const_interface i, /* out */iterator itr, void* key);
/* find the minimum element which is greater than key */
extern inline void     immap_itr_find_upper(const_interface i, /* out */iterator itr, void* key);
extern inline void*    immap_itr_remove (_interface i, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator immap_itr_begin  (const_interface i);
extern inline const_iterator immap_itr_end    (const_interface i);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_immap_destroy)    (object o);
typedef       void     (*pf_immap_clear)      (object o);
typedef       void     (*pf_immap_clear_v)    (object o, pf_ref_dispose_v dispose, void* context);
typedef       int      (*pf_immap_size)       (const_object o);
typedef       bool     (*pf_immap_empty)      (const_object o);
typedef       void     (*pf_immap_insert)     (object o, const void* key, void* value);
typedef       bool     (*pf_immap_contains)   (const_object o, const void* key);
typedef       int      (*pf_immap_count)      (const_object o, const void* key);
typedef       bool     (*pf_immap_remove)     (object o, void* key);

typedef       iterator (*pf_immap_itr_create) (const_object o, itr_pos pos);
typedef       void     (*pf_immap_itr_assign) (const_object o, iterator itr, itr_pos pos);
typedef       void     (*pf_immap_itr_find_lower)(const_object o, iterator itr, void* key);
typedef       void     (*pf_immap_itr_find_upper)(const_object o, iterator itr, void* key);
typedef       void*    (*pf_immap_itr_remove) (object o, iterator itr);
typedef const_iterator (*pf_immap_itr_begin)  (const_object o);
typedef const_iterator (*pf_immap_itr_end)    (const_object o);

struct immap_vtable {
	/* public */
	pf_immap_destroy        __destroy;
	pf_immap_clear          __clear;
	pf_immap_clear_v        __clear_v;
	pf_immap_size           __size;
	pf_immap_empty          __empty;
	pf_immap_insert         __insert;
	pf_immap_contains       __contains;
	pf_immap_count          __count;
	pf_immap_remove         __remove;

	pf_immap_itr_create     __itr_create;
	pf_immap_itr_assign     __itr_assign;
	pf_immap_itr_find_lower __itr_find_lower;
	pf_immap_itr_find_upper __itr_find_upper;
	pf_immap_itr_remove     __itr_remove;
	pf_immap_itr_begin      __itr_begin;
	pf_immap_itr_end        __itr_end;
};

#endif /* _INTERFACE_MAP_H_ */
