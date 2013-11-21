#ifndef _CLASS_VERIFY_SIZED_ARRAY_H_
#define _CLASS_VERIFY_SIZED_ARRAY_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* create an Object* list which holds instance of Object*s, the container will manage the life time of the Object*s. */
Object*        oarray_create          (unknown_traits content_traits, allocator alc);

void           oarray_destroy         (      Object* cntr);
Object*        oarray_clone           (const Object* cntr);
bool           oarray_equals          (const Object* cntr, const Object* other);
int            oarray_compare_to      (const Object* cntr, const Object* other);
hashcode       oarray_hashcode        (const Object* cntr);

void           oarray_clear           (      Object* cntr);
void           oarray_foreach         (      Object* cntr, pf_ref_process_v process, void* context);
int            oarray_size            (const Object* cntr);
bool           oarray_empty           (const Object* cntr);
/* the return value is a reference which is allocated on the __global_default_heap, you should clean it up yourself */
const unknown* oarray_front           (const Object* cntr);
const unknown* oarray_back            (const Object* cntr);
const unknown* oarray_at              (const Object* cntr, int index);
void           oarray_add_front       (      Object* cntr, const unknown* __ref);
void           oarray_add_back        (      Object* cntr, const unknown* __ref);
void           oarray_remove_front    (      Object* cntr);
void           oarray_remove_back     (      Object* cntr);
bool           oarray_contains        (const Object* cntr, const unknown* __ref);
bool           oarray_remove          (      Object* cntr, const unknown* __ref);
iterator       oarray_itr_create      (const Object* cntr, itr_pos pos);
void           oarray_itr_assign      (const Object* cntr, iterator itr, itr_pos pos);
void           oarray_itr_find        (const Object* cntr, iterator itr, const unknown* __ref);
void           oarray_itr_remove      (      Object* cntr, iterator itr);
const_iterator oarray_itr_begin       (const Object* cntr);
const_iterator oarray_itr_end         (const Object* cntr);

#endif /* _CLASS_VERIFY_SIZED_ARRAY_H_ */
