#ifndef _OBJECT_SKIPLIST_H_
#define _OBJECT_SKIPLIST_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* if alc is NULL, create_v will create an osplay with multi-pool allocator to gain best efficiency */
Object*  oslist_create          (unknown_traits* content_traits, allocator alc);

void     oslist_destroy         (Object* o);
Object*  oslist_clone           (const Object* o);
bool     oslist_equals          (const Object* o, const Object* other);
int      oslist_compare_to      (const Object* o, const Object* other);
hashcode oslist_hashcode        (const Object* o);
void     oslist_clear           (Object* o);
int      oslist_size            (const Object* o);
bool     oslist_empty           (const Object* o);
void     oslist_insert_s        (Object* o, const unknown* __ref);
void     oslist_replace_s       (Object* o, const unknown* __ref);
void     oslist_insert_m        (Object* o, const unknown* __ref);
bool     oslist_contains        (const Object* o, const unknown* __ref);
int      oslist_count           (const Object* o, const unknown* __ref);
bool     oslist_remove_s        (Object* o, const unknown* __ref);
int      oslist_remove_m        (Object* o, const unknown* __ref);

iterator oslist_itr_create      (const Object* o, itr_pos pos);
void     oslist_itr_assign      (const Object* o, iterator itr, itr_pos pos);
void     oslist_itr_find        (const Object* o, iterator itr, const unknown* __ref);
void     oslist_itr_find_lower  (const Object* o, iterator itr, const unknown* __ref);
void     oslist_itr_find_upper  (const Object* o, iterator itr, const unknown* __ref);
void     oslist_itr_remove      (Object* o, iterator itr);

const_iterator oslist_itr_begin (const Object* o);
const_iterator oslist_itr_end   (const Object* o);

#endif /* _OBJECT_SKIPLIST_H_ */
