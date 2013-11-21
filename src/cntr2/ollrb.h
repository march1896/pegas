#ifndef _OBJECT_LEFTLEAN_REDBLACK_TREE_H_
#define _OBJECT_LEFTLEAN_REDBLACK_TREE_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* if alc is NULL, create will create an osplay with multi-pool allocator to gain best efficiency */
Object*   ollrb_create          (unknown_traits content_traits, allocator alc);

void     ollrb_destroy         (Object* o);
Object*   ollrb_clone           (const Object* o);
bool     ollrb_equals          (const Object* o, const Object* other);
int      ollrb_compare_to      (const Object* o, const Object* other);
hashcode ollrb_hashcode        (const Object* o);
void     ollrb_clear           (Object* o);
int      ollrb_size            (const Object* o);
bool     ollrb_empty           (const Object* o);
void     ollrb_insert_s        (Object* o, const unknown* __ref);
void     ollrb_replace_s       (Object* o, const unknown* __ref);
void     ollrb_insert_m        (Object* o, const unknown* __ref);
bool     ollrb_contains        (const Object* o, const unknown* __ref);
int      ollrb_count           (const Object* o, const unknown* __ref);
bool     ollrb_remove_s        (Object* o, const unknown* __ref);
int      ollrb_remove_m        (Object* o, const unknown* __ref);

iterator ollrb_itr_create      (const Object* o, itr_pos pos);
void     ollrb_itr_assign      (const Object* o, iterator itr, itr_pos pos);
void     ollrb_itr_find        (const Object* o, iterator itr, const void* __ref);
void     ollrb_itr_find_lower  (const Object* o, iterator itr, const void* __ref);
void     ollrb_itr_find_upper  (const Object* o, iterator itr, const void* __ref);
void     ollrb_itr_remove      (Object* o, iterator itr);

const_iterator ollrb_itr_begin (const Object* o);
const_iterator ollrb_itr_end   (const Object* o);

#endif /* _OBJECT_LEFTLEAN_REDBLACK_TREE_H_ */
