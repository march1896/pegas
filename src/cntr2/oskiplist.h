#ifndef _OBJECT_SKIPLIST_H_
#define _OBJECT_SKIPLIST_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* if alc is NULL, create_v will create an osplay with multi-pool allocator to gain best efficiency */
object   oslist_create          (unknown_traits content_traits, allocator alc);

void     oslist_destroy         (object o);
object   oslist_clone           (const_object o);
bool     oslist_equals          (const_object o, const_object other);
int      oslist_compare_to      (const_object o, const_object other);
hashcode oslist_hashcode        (const_object o);
void     oslist_clear           (object o);
int      oslist_size            (const_object o);
bool     oslist_empty           (const_object o);
void     oslist_insert_s        (object o, const_unknown __ref);
void     oslist_replace_s       (object o, const_unknown __ref);
void     oslist_insert_m        (object o, const_unknown __ref);
bool     oslist_contains        (const_object o, const_unknown __ref);
int      oslist_count           (const_object o, const_unknown __ref);
bool     oslist_remove_s        (object o, const_unknown __ref);
int      oslist_remove_m        (object o, const_unknown __ref);

iterator oslist_itr_create      (const_object o, itr_pos pos);
void     oslist_itr_assign      (const_object o, iterator itr, itr_pos pos);
void     oslist_itr_find        (const_object o, iterator itr, const_unknown __ref);
void     oslist_itr_find_lower  (const_object o, iterator itr, const_unknown __ref);
void     oslist_itr_find_upper  (const_object o, iterator itr, const_unknown __ref);
void     oslist_itr_remove      (object o, iterator itr);

const_iterator oslist_itr_begin (const_object o);
const_iterator oslist_itr_end   (const_object o);

#endif /* _OBJECT_SKIPLIST_H_ */
