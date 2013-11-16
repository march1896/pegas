#ifndef _OBJECT_LEFTLEAN_REDBLACK_TREE_H_
#define _OBJECT_LEFTLEAN_REDBLACK_TREE_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* if alc is NULL, create will create an osplay with multi-pool allocator to gain best efficiency */
object   ollrb_create          (unknown_traits content_traits, allocator alc);

void     ollrb_destroy         (object o);
object   ollrb_clone           (const_object o);
bool     ollrb_equals          (const_object o, const_object other);
int      ollrb_compare_to      (const_object o, const_object other);
hashcode ollrb_hashcode        (const_object o);
void     ollrb_clear           (object o);
int      ollrb_size            (const_object o);
bool     ollrb_empty           (const_object o);
void     ollrb_insert_s        (object o, const_unknown __ref);
void     ollrb_replace_s       (object o, const_unknown __ref);
void     ollrb_insert_m        (object o, const_unknown __ref);
bool     ollrb_contains        (const_object o, const_unknown __ref);
int      ollrb_count           (const_object o, const_unknown __ref);
bool     ollrb_remove_s        (object o, const_unknown __ref);
int      ollrb_remove_m        (object o, const_unknown __ref);

iterator ollrb_itr_create      (const_object o, itr_pos pos);
void     ollrb_itr_assign      (const_object o, iterator itr, itr_pos pos);
void     ollrb_itr_find        (const_object o, iterator itr, const void* __ref);
void     ollrb_itr_find_lower  (const_object o, iterator itr, const void* __ref);
void     ollrb_itr_find_upper  (const_object o, iterator itr, const void* __ref);
void     ollrb_itr_remove      (object o, iterator itr);

const_iterator ollrb_itr_begin (const_object o);
const_iterator ollrb_itr_end   (const_object o);

#endif /* _OBJECT_LEFTLEAN_REDBLACK_TREE_H_ */
