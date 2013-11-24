#ifndef _INTERFACE_MAP_H_
#define _INTERFACE_MAP_H_

/* the interface functions which support, used by clients */
#include <cntr2/oo_model.h>
#include <cntr2/idef.h>

typedef struct map_pair_t {
	const unknown* key;
	unknown*       value;
} map_pair;

extern inline void           imap_clear            (Object* obj);
extern inline int            imap_size             (const Object* obj);
extern inline bool           imap_empty            (const Object* obj);
/* if <key, old_value> pair in the map, the old_value will be updated, and the old_value 
 * will be returned, if not, return NULL. */
extern inline void           imap_insert           (Object* obj, const unknown* key, const unknown* value);
extern inline void           imap_insert_p         (Object* obj, const map_pair* pair);
extern inline bool           imap_contains         (const Object* obj, const unknown* key);
/* return NULL if the key is not in the map */
extern inline const unknown* imap_findbykey        (const Object* obj, const unknown* key);
extern inline void           imap_remove           (Object* obj, const unknown* key);

extern inline iterator       imap_itr_create       (const Object* obj, itr_pos pos);
extern inline void           imap_itr_assign       (const Object* obj, /* out */iterator itr, itr_pos pos);
/* points to end if key is not in the map */
extern inline void           imap_itr_find         (const Object* obj, /* out */iterator itr, const unknown* key);
extern inline void           imap_itr_remove       (Object* obj, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator imap_itr_begin        (const Object* obj);
extern inline const_iterator imap_itr_end          (const Object* obj);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void           (*pf_imap_clear)      (Object* c);
typedef       int            (*pf_imap_size)       (const Object* c);
typedef       bool           (*pf_imap_empty)      (const Object* c);
typedef       void           (*pf_imap_insert)     (Object* c, const unknown* key, const unknown* value);
typedef       bool           (*pf_imap_contains)   (const Object* c, const unknown* key);
typedef       const unknown* (*pf_imap_findbykey)  (const Object* c, const unknown* key);
typedef       void*          (*pf_imap_remove)     (Object* c, const unknown* key);

typedef       iterator       (*pf_imap_itr_create) (const Object* c, itr_pos pos);
typedef       void           (*pf_imap_itr_assign) (const Object* c, iterator itr, itr_pos pos);
typedef       void           (*pf_imap_itr_find)   (const Object* c, iterator itr, const unknown* key);
typedef       void           (*pf_imap_itr_remove) (Object* c, iterator itr);
typedef       const_iterator (*pf_imap_itr_begin)  (const Object* c);
typedef       const_iterator (*pf_imap_itr_end)    (const Object* c);

struct imap_vtable {
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
extern inline void           immap_destroy          (Object* i);
extern inline void           immap_clear            (Object* i);
extern inline int            immap_size             (const Object* i);
extern inline bool           immap_empty            (const Object* i);
extern inline void           immap_insert           (Object* i, const unknown* key, const unknown* value);
extern inline bool           immap_contains         (const Object* i, const unknown* key);
/* return number of reference of key */
extern inline int            immap_count            (const Object* i, const unknown* key);
extern inline bool           immap_remove           (Object* i, const unknown* key);

extern inline iterator       immap_itr_create       (const Object* i, itr_pos pos);
extern inline void           immap_itr_assign       (const Object* i, /* out */iterator itr, itr_pos pos);
/* find the minimum element which is greater or equal to key */
extern inline void           immap_itr_find_lower   (const Object* i, /* out */iterator itr, const unknown* key);
/* find the minimum element which is greater than key */
extern inline void           immap_itr_find_upper   (const Object* i, /* out */iterator itr, const unknown* key);
extern inline void           immap_itr_remove       (Object* i, iterator itr);
/* return a iterator, maybe forward/bidirectional/random accessed. */
extern inline const_iterator immap_itr_begin        (const Object* i);
extern inline const_iterator immap_itr_end          (const Object* i);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void           (*pf_immap_destroy)    (Object* o);
typedef       void           (*pf_immap_clear)      (Object* o);
typedef       int            (*pf_immap_size)       (const Object* o);
typedef       bool           (*pf_immap_empty)      (const Object* o);
typedef       void           (*pf_immap_insert)     (Object* o, const unknown* key, const unknown* value);
typedef       bool           (*pf_immap_contains)   (const Object* o, const unknown* key);
typedef       int            (*pf_immap_count)      (const Object* o, const unknown* key);
typedef       bool           (*pf_immap_remove)     (Object* o, const unknown* key);

typedef       iterator       (*pf_immap_itr_create) (const Object* o, itr_pos pos);
typedef       void           (*pf_immap_itr_assign) (const Object* o, iterator itr, itr_pos pos);
typedef       void           (*pf_immap_itr_find_lower)(const Object* o, iterator itr, const unknown* key);
typedef       void           (*pf_immap_itr_find_upper)(const Object* o, iterator itr, const unknown* key);
typedef       void           (*pf_immap_itr_remove) (Object* o, iterator itr);
typedef const_iterator       (*pf_immap_itr_begin)  (const Object* o);
typedef const_iterator       (*pf_immap_itr_end)    (const Object* o);

struct immap_vtable {
	/* public */
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
