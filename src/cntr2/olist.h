#ifndef _OBJECT_DOUBLE_LINK_LIST_H_
#define _OBJECT_DOUBLE_LINK_LIST_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* create an object list which holds instance of objects, the container will manage the life time of the objects. */
Object*        olist_create          (unknown_traits content_traits, allocator alc);

void           olist_destroy         (      Object* o);
Object*        olist_clone           (const Object* o);
bool           olist_equals          (const Object* o, const Object* other);
int            olist_compare_to      (const Object* o, const Object* other);
hashcode       olist_hashcode        (const Object* o);

void           olist_clear           (      Object* o);
void           olist_foreach         (      Object* o, pf_ref_process_v process, void* context);
int            olist_size            (const Object* o);
bool           olist_empty           (const Object* o);
/* the return value is a reference which is allocated on the __global_default_heap, you should clean it up yourself */
const unknown* olist_front           (const Object* o);
const unknown* olist_back            (const Object* o);
void           olist_add_front       (      Object* o, const unknown* __ref);
void           olist_add_back        (      Object* o, const unknown* __ref);
void           olist_remove_front    (      Object* o);
void           olist_remove_back     (      Object* o);
bool           olist_contains        (const Object* o, const unknown* __ref);
bool           olist_remove          (      Object* o, const unknown* __ref);
iterator       olist_itr_create      (const Object* o, itr_pos pos);
void           olist_itr_assign      (const Object* o, iterator itr, itr_pos pos);
void           olist_itr_find        (const Object* o, iterator itr, const unknown* __ref);
void           olist_itr_remove      (      Object* o, iterator itr);
void           olist_insert_before   (      Object* o, iterator itr, const unknown* n_ref);
void           olist_insert_after    (      Object* o, iterator itr, const unknown* n_ref);
const_iterator olist_itr_begin       (const Object* o);
const_iterator olist_itr_end         (const Object* o);

#endif /* _OBJECT_DOUBLE_LINK_LIST_H_ */
