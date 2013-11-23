#ifndef _OBJECT_SPLAYTREE_H_
#define _OBJECT_SPLAYTREE_H_

#include <cntr2/oo_model.h>
#include <cntr2/oallocator.h>

/* if alc is NULL, create_v will create an osplay with multi-pool allocator to gain best efficiency */
Object*         splayset_create          (unknown_traits* content_traits, allocator alc);
void            splayset_destroy         (Object* o);
Object*         splayset_clone           (const Object* o);
bool            splayset_equals          (const Object* o, const Object* other);
int             splayset_compare_to      (const Object* o, const Object* other);
hashcode        splayset_hashcode        (const Object* o);
void            splayset_clear           (Object* o);
int             splayset_size            (const Object* o);
bool            splayset_empty           (const Object* o);
void            splayset_insert_s        (Object* o, const unknown* __ref);
void            splayset_replace_s       (Object* o, const unknown* __ref);
void            splayset_insert_m        (Object* o, const unknown* __ref);
bool            splayset_contains        (const Object* o, const unknown* __ref);
int             splayset_count_m         (const Object* o, const unknown* __ref);
bool            splayset_remove_s        (Object* o, const unknown* __ref);
int             splayset_remove_m        (Object* o, const unknown* __ref);

iterator        splayset_itr_create      (const Object* o, itr_pos pos);
void            splayset_itr_assign      (const Object* o, iterator itr, itr_pos pos);
void            splayset_itr_find_s      (const Object* o, iterator itr, const unknown* __ref);
void            splayset_itr_find_lower_m(const Object* o, iterator itr, const unknown* __ref);
void            splayset_itr_find_upper_m(const Object* o, iterator itr, const unknown* __ref);
void            splayset_itr_remove      (Object* o, iterator itr);

const_iterator  splayset_itr_begin       (const Object* o);
const_iterator  splayset_itr_end         (const Object* o);

// TODO: should we have the detailed implementation for each container just for a virtual function call 
// performance?

// /* if alc is NULL, create_v will create an osplay with multi-pool allocator to gain best efficiency */
// object  splaymap_create_v        (pf_ref_compare ref_comp, allocator alc);
// object  splaymap_create          (pf_ref_compare ref_comp);
// void     splaymap_destroy         (object o);
// void     splaymap_clear           (object o);
// int      splaymap_size            (const Object* o);
// bool     splaymap_empty           (const Object* o);
// void*    splaymap_insert_s        (object o, const void* key, void* value);
// void     splaymap_insert_m        (object o, const void* key, void* value);
// bool     splaymap_contains        (const Object* o, const void* key);
// void*    splaymap_findbykey_s     (const Object* o, const void* key);
// int      splaymap_count_m         (const Object* o, const void* key);
// void*    splaymap_remove_s        (object o, void* key);
// void     splaymap_remove_m        (object o, void* key);
// 
// iterator splaymap_itr_create      (const Object* o, itr_pos pos);
// void     splaymap_itr_assign      (const Object* o, iterator itr, itr_pos pos);
// void     splaymap_itr_find_s      (const Object* o, iterator itr, const void* key);
// void     splaymap_itr_find_lower_m(const Object* o, iterator itr, const void* key);
// void     splaymap_itr_find_upper_m(const Object* o, iterator itr, const void* key);
// void*    splaymap_itr_remove      (object o, iterator itr);
// 
// const_iterator splaymap_itr_begin (const Object* o);
// const_iterator splaymap_itr_end   (const Object* o);


#endif /* _OBJECT_SPLAYTREE_H_ */
