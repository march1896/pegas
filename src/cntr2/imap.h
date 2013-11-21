#ifndef _INTERFACE_MAP_H_
#define _INTERFACE_MAP_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>

typedef struct map_pair_t {
	const void* key;
	void*       value;
} map_pair;

extern inline void     imap_destroy          (_interface* ic);
extern inline void     imap_clear            (_interface* ic);
extern inline int      imap_size             (const _interface* ic);
extern inline bool     imap_empty            (const _interface* ic);
/* if <key, old_value> pair in the map, the old_value will be updated, and the old_value 
 * will be returned, if not, return NULL. */
extern inline void*    imap_insert           (_interface* ic, const void* key, void* value);
extern inline bool     imap_contains         (const _interface* ic, const void* key);
/* return NULL if the key is not in the map */
extern inline void*    imap_findbykey        (const _interface* ic, const void* key);
/* return NULL if key is not in the map, or the <key, value> pair will be removed from the map */
extern inline void*    imap_remove           (_interface* ic, void* key);

extern inline iterator imap_itr_create       (const _interface* ic, itr_pos pos);
extern inline void     imap_itr_assign       (const _interface* ic, /* out */iterator itr, itr_pos pos);
/* points to end if key is not in the map */
extern inline void     imap_itr_find         (const _interface* ic, /* out */iterator itr, void* key);
extern inline void*    imap_itr_remove       (_interface* ic, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator imap_itr_begin  (const _interface* ic);
extern inline const_iterator imap_itr_end    (const _interface* ic);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_imap_destroy)    (Object* c);
typedef       void     (*pf_imap_clear)      (Object* c);
typedef       int      (*pf_imap_size)       (const Object* c);
typedef       bool     (*pf_imap_empty)      (const Object* c);
typedef       void*    (*pf_imap_insert)     (Object* c, const void* key, void* value);
typedef       bool     (*pf_imap_contains)   (const Object* c, const void* key);
typedef       void*    (*pf_imap_findbykey)  (const Object* c, const void* key);
typedef       void*    (*pf_imap_remove)     (Object* c, void* key);

typedef       iterator (*pf_imap_itr_create) (const Object* c, itr_pos pos);
typedef       void     (*pf_imap_itr_assign) (const Object* c, iterator itr, itr_pos pos);
typedef       void     (*pf_imap_itr_find)   (const Object* c, iterator itr, void* key);
typedef       void*    (*pf_imap_itr_remove) (Object* c, iterator itr);
typedef const_iterator (*pf_imap_itr_begin)  (const Object* c);
typedef const_iterator (*pf_imap_itr_end)    (const Object* c);

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
extern inline void     immap_destroy    (_interface* i);
extern inline void     immap_clear      (_interface* i);
extern inline int      immap_size       (const _interface* i);
extern inline bool     immap_empty      (const _interface* i);
extern inline void     immap_insert     (_interface* i, const void* key, void* value);
extern inline bool     immap_contains   (const _interface* i, const void* key);
/* return number of reference of key */
extern inline int      immap_count      (const _interface* i, const void* key);
extern inline bool     immap_remove     (_interface* i, void* key);

extern inline iterator immap_itr_create (const _interface* i, itr_pos pos);
extern inline void     immap_itr_assign (const _interface* i, /* out */iterator itr, itr_pos pos);
/* find the minimum element which is greater or equal to key */
extern inline void     immap_itr_find_lower(const _interface* i, /* out */iterator itr, void* key);
/* find the minimum element which is greater than key */
extern inline void     immap_itr_find_upper(const _interface* i, /* out */iterator itr, void* key);
extern inline void*    immap_itr_remove (_interface* i, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator immap_itr_begin  (const _interface* i);
extern inline const_iterator immap_itr_end    (const _interface* i);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_immap_destroy)    (Object* o);
typedef       void     (*pf_immap_clear)      (Object* o);
typedef       int      (*pf_immap_size)       (const Object* o);
typedef       bool     (*pf_immap_empty)      (const Object* o);
typedef       void     (*pf_immap_insert)     (Object* o, const void* key, void* value);
typedef       bool     (*pf_immap_contains)   (const Object* o, const void* key);
typedef       int      (*pf_immap_count)      (const Object* o, const void* key);
typedef       bool     (*pf_immap_remove)     (Object* o, void* key);

typedef       iterator (*pf_immap_itr_create) (const Object* o, itr_pos pos);
typedef       void     (*pf_immap_itr_assign) (const Object* o, iterator itr, itr_pos pos);
typedef       void     (*pf_immap_itr_find_lower)(const Object* o, iterator itr, void* key);
typedef       void     (*pf_immap_itr_find_upper)(const Object* o, iterator itr, void* key);
typedef       void*    (*pf_immap_itr_remove) (Object* o, iterator itr);
typedef const_iterator (*pf_immap_itr_begin)  (const Object* o);
typedef const_iterator (*pf_immap_itr_end)    (const Object* o);

struct immap_vtable {
	/* public */
	pf_immap_destroy        __destroy;
	pf_immap_clear          __clear;
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
