#ifndef _OBJECT_VERIFY_SIZED_ARRAY_H_
#define _OBJECT_VERIFY_SIZED_ARRAY_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* create an object list which holds instance of objects, the container will manage the life time of the objects. */
object         oarray_create          (unknown_traits content_traits, allocator alc);

void           oarray_destroy         (      object o);
object         oarray_clone           (const_object o);
bool           oarray_equals          (const_object o, const_object other);
int            oarray_compare_to      (const_object o, const_object other);
hashcode       oarray_hashcode        (const_object o);

void           oarray_clear           (      object o);
void           oarray_foreach         (      object o, pf_ref_process_v process, void* context);
int            oarray_size            (const_object o);
bool           oarray_empty           (const_object o);
/* the return value is a reference which is allocated on the __global_default_heap, you should clean it up yourself */
const_unknown  oarray_front           (const_object o);
const_unknown  oarray_back            (const_object o);
const_unknown  oarray_at              (const_object o);
void           oarray_add_front       (      object o, const_unknown __ref);
void           oarray_add_back        (      object o, const_unknown __ref);
void           oarray_remove_front    (      object o);
void           oarray_remove_back     (      object o);
bool           oarray_contains        (const_object o, const_unknown __ref);
bool           oarray_remove          (      object o, const_unknown __ref);
iterator       oarray_itr_create      (const_object o, itr_pos pos);
void           oarray_itr_assign      (const_object o, iterator itr, itr_pos pos);
void           oarray_itr_find        (const_object o, iterator itr, const_unknown __ref);
void           oarray_itr_remove      (      object o, iterator itr);
const_iterator oarray_itr_begin       (const_object o);
const_iterator oarray_itr_end         (const_object o);

#endif /* _OBJECT_VERIFY_SIZED_ARRAY_H_ */
