#ifndef _OBJECT_SPLAYTREE_H_
#define _OBJECT_SPLAYTREE_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* if alc is NULL, create_v will create an osplay with multi-pool allocator to gain best efficiency */
object         splayset_create          (pf_ref_compare ref_comp, allocator alc);
object         splayset_create_v        (pf_ref_compare_v compv, void* cp_context, allocator alc);
void            splayset_destroy         (object o);
void            splayset_clear           (object o);
void            splayset_clear_v         (object o, pf_ref_dispose_v dispose, void* context);
int             splayset_size            (const_object o);
bool            splayset_empty           (const_object o);
void*           splayset_insert_s        (object o, const void* __ref);
void            splayset_insert_m        (object o, const void* __ref);
bool            splayset_contains        (const_object o, const void* __ref);
int             splayset_count_m         (const_object o, const void* __ref);
bool            splayset_remove          (object o, void* __ref);

iterator        splayset_itr_create      (const_object o, itr_pos pos);
void            splayset_itr_assign      (const_object o, iterator itr, itr_pos pos);
void            splayset_itr_find_s      (const_object o, iterator itr, const void* __ref);
void            splayset_itr_find_lower_m(const_object o, iterator itr, const void* __ref);
void            splayset_itr_find_upper_m(const_object o, iterator itr, const void* __ref);
void*           splayset_itr_remove      (object o, iterator itr);

const_iterator  splayset_itr_begin       (const_object o);
const_iterator  splayset_itr_end         (const_object o);

// TODO: should we have the detailed implementation for each container just for a virtual function call 
// performance?

// /* if alc is NULL, create_v will create an osplay with multi-pool allocator to gain best efficiency */
// object  splaymap_create_v        (pf_ref_compare ref_comp, allocator alc);
// object  splaymap_create          (pf_ref_compare ref_comp);
// void     splaymap_destroy         (object o);
// void     splaymap_clear           (object o);
// int      splaymap_size            (const_object o);
// bool     splaymap_empty           (const_object o);
// void*    splaymap_insert_s        (object o, const void* key, void* value);
// void     splaymap_insert_m        (object o, const void* key, void* value);
// bool     splaymap_contains        (const_object o, const void* key);
// void*    splaymap_findbykey_s     (const_object o, const void* key);
// int      splaymap_count_m         (const_object o, const void* key);
// void*    splaymap_remove_s        (object o, void* key);
// void     splaymap_remove_m        (object o, void* key);
// 
// iterator splaymap_itr_create      (const_object o, itr_pos pos);
// void     splaymap_itr_assign      (const_object o, iterator itr, itr_pos pos);
// void     splaymap_itr_find_s      (const_object o, iterator itr, const void* key);
// void     splaymap_itr_find_lower_m(const_object o, iterator itr, const void* key);
// void     splaymap_itr_find_upper_m(const_object o, iterator itr, const void* key);
// void*    splaymap_itr_remove      (object o, iterator itr);
// 
// const_iterator splaymap_itr_begin (const_object o);
// const_iterator splaymap_itr_end   (const_object o);


#endif /* _OBJECT_SPLAYTREE_H_ */
