#ifndef _OBJECT_DOUBLE_LINK_LIST_H_
#define _OBJECT_DOUBLE_LINK_LIST_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* create an odlist which holds instance of objects, the container will manage the life time of the objects. */
object        o_dlist_create          (pf_ref_clone_v clone, pf_ref_destroy_v destroy, pf_ref_equals_v equals, allocator alc);

void           o_dlist_destroy         (      object o);
object         o_dlist_clone           (const_object o);
bool           o_dlist_equals          (const_object o, const_object other);
int            o_dlist_compare_to      (const_object o, const_object other);
hashcode       o_dlist_hashcode        (const_object o);
void           o_dlist_clear           (      object o);
void           o_dlist_foreach         (      object o, pf_ref_process_v process, void* context);
int            o_dlist_size            (const_object o);
bool           o_dlist_empty           (const_object o);
const_unknown  o_dlist_front           (const_object o);
const_unknown  o_dlist_back            (const_object o);
void           o_dlist_add_front       (      object o, const_unknown __ref);
void           o_dlist_add_back        (      object o, const_unknown __ref);
void           o_dlist_remove_front    (      object o);
void           o_dlist_remove_back     (      object o);
bool           o_dlist_contains        (const_object o, const_unknown __ref);
bool           o_dlist_remove          (      object o, const_unknown __ref);
iterator       o_dlist_itr_create      (const_object o, itr_pos pos);
void           o_dlist_itr_assign      (const_object o, iterator itr, itr_pos pos);
void           o_dlist_itr_find        (const_object o, iterator itr, const_unknown __ref);
void           o_dlist_itr_remove      (      object o, iterator itr);
void           o_dlist_insert_before   (      object o, iterator itr, const_unknown n_ref);
void           o_dlist_insert_after    (      object o, iterator itr, const_unknown n_ref);
const_iterator o_dlist_itr_begin       (const_object o);
const_iterator o_dlist_itr_end         (const_object o);

#endif /* _OBJECT_DOUBLE_LINK_LIST_H_ */
