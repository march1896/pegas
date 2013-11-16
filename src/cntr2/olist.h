#ifndef _OBJECT_DOUBLE_LINK_LIST_H_
#define _OBJECT_DOUBLE_LINK_LIST_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* create an object list which holds instance of objects, the container will manage the life time of the objects. */
object         olist_create          (unknown_traits content_traits, allocator alc);

void           olist_destroy         (      object o);
object         olist_clone           (const_object o);
bool           olist_equals          (const_object o, const_object other);
int            olist_compare_to      (const_object o, const_object other);
hashcode       olist_hashcode        (const_object o);

void           olist_clear           (      object o);
void           olist_foreach         (      object o, pf_ref_process_v process, void* context);
int            olist_size            (const_object o);
bool           olist_empty           (const_object o);
/* the return value is a reference which is allocated on the __global_default_heap, you should clean it up yourself */
const_unknown  olist_front           (const_object o);
const_unknown  olist_back            (const_object o);
void           olist_add_front       (      object o, const_unknown __ref);
void           olist_add_back        (      object o, const_unknown __ref);
void           olist_remove_front    (      object o);
void           olist_remove_back     (      object o);
bool           olist_contains        (const_object o, const_unknown __ref);
bool           olist_remove          (      object o, const_unknown __ref);
iterator       olist_itr_create      (const_object o, itr_pos pos);
void           olist_itr_assign      (const_object o, iterator itr, itr_pos pos);
void           olist_itr_find        (const_object o, iterator itr, const_unknown __ref);
void           olist_itr_remove      (      object o, iterator itr);
void           olist_insert_before   (      object o, iterator itr, const_unknown n_ref);
void           olist_insert_after    (      object o, iterator itr, const_unknown n_ref);
const_iterator olist_itr_begin       (const_object o);
const_iterator olist_itr_end         (const_object o);

#endif /* _OBJECT_DOUBLE_LINK_LIST_H_ */
