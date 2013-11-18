#ifndef _OBJECT_SKIPLIST_H_
#define _OBJECT_SKIPLIST_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* if alc is NULL, create_v will create an osplay with multi-pool allocator to gain best efficiency */
object   oskiplist_create          (pf_ref_compare ref_comp, allocator alc);
object   oskiplist_create_v        (pf_ref_compare_v ref_comp_v, void* comp_context, allocator alc);
void     oskiplist_destroy         (object o);
object   oskiplist_clone           (const_object o);
bool     oskiplist_equals          (const_object o, const_object other);
int      oskiplist_compare_to      (const_object o, const_object other);
hashcode oskiplist_hashcode        (const_object o);
void     oskiplist_clear           (object o);
int      oskiplist_size            (const_object o);
bool     oskiplist_empty           (const_object o);
void     oskiplist_insert_s        (object o, const_unknown __ref);
void     oskiplist_insert_m        (object o, const_unknown __ref);
bool     oskiplist_contains        (const_object o, const_unknown __ref);
int      oskiplist_count           (const_object o, const_unknown __ref);
bool     oskiplist_remove_s        (object o, const_unknown __ref);
int      oskiplist_remove_m        (object o, const_unknown __ref);

iterator oskiplist_itr_create      (const_object o, itr_pos pos);
void     oskiplist_itr_assign      (const_object o, iterator itr, itr_pos pos);
void     oskiplist_itr_find        (const_object o, iterator itr, const_unknown __ref);
void     oskiplist_itr_find_lower  (const_object o, iterator itr, const_unknown __ref);
void     oskiplist_itr_find_upper  (const_object o, iterator itr, const_unknown __ref);
void*    oskiplist_itr_remove      (object o, iterator itr);

const_iterator oskiplist_itr_begin (const_object o);
const_iterator oskiplist_itr_end   (const_object o);

#endif /* _OBJECT_SKIPLIST_H_ */
