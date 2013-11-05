#ifndef _OBJECT_DOUBLE_LINK_LIST_H_
#define _OBJECT_DOUBLE_LINK_LIST_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* create an odlist which holds instance of objects, the container will manage the life time of the objects. */
object*        o_dlist_create          (pf_ref_clone_v clone, pf_ref_destroy_v destroy, pf_ref_equals_v equals, allocator alc);

void           o_dlist_destroy         (      object* o);
void           o_dlist_clear           (      object* o);
void           o_dlist_foreach         (      object* o, pf_ref_process_v process, void* context);
int            o_dlist_size            (const object* o);
bool           o_dlist_empty           (const object* o);
const_unknown  o_dlist_front           (const object* o);
const_unknown  o_dlist_back            (const object* o);
void           o_dlist_add_front       (      object* o, const_unknown __ref);
void           o_dlist_add_back        (      object* o, const_unknown __ref);
void           o_dlist_remove_front    (      object* o);
void           o_dlist_remove_back     (      object* o);
bool           o_dlist_contains        (const object* o, const_unknown __ref);
bool           o_dlist_remove          (      object* o, const_unknown __ref);
iterator       o_dlist_itr_create      (const object* o, itr_pos pos);
void           o_dlist_itr_assign      (const object* o, iterator itr, itr_pos pos);
void           o_dlist_itr_find        (const object* o, iterator itr, const_unknown __ref);
void           o_dlist_itr_remove      (      object* o, iterator itr);
void           o_dlist_insert_before   (      object* o, iterator itr, const_unknown n_ref);
void           o_dlist_insert_after    (      object* o, iterator itr, const_unknown n_ref);
const_iterator o_dlist_itr_begin       (const object* o);
const_iterator o_dlist_itr_end         (const object* o);

#endif /* _OBJECT_DOUBLE_LINK_LIST_H_ */
