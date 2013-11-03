#ifndef _OBJECT_ALLOCATOR_H_
#define _OBJECT_ALLOCATOR_H_

#include <idef.h>
#include <heap_def.h>

/* 
 * by using the macros, it's not clear to view the methods supported by this object.
 * the methods are:
 * 1, allocator_join
 * 2, allocator_acquire_v/allocator_acquire_c
 * 3, allocator_release_v/allocator_release_c
 * 4, allocator_get_parent
 * 5, allocator_walk
 *
 * the 2 and 3 are methods name depends the compile macros, so macro
 * allocator_alloc   = allocator_acquire_v/allocator_acquire_c
 * allocator_dealloc = allocator_release_v/allocator_release_c
 * handles this situation, after this macro, the methods can be describes as:
 * 1, allocator_join
 * 2, allocator_alloc
 * 3, allocator_dealloc
 * 4, allocator_get_parent
 * 5, allocator_walk
 */

/* 
 * oallocator implements iallocator interface, in fact it implements the 'heap interface'
 * implicitly. recall the heap definition in heap_def.h
 * it has two method pf_alloc, pf_dealloc and a heap_handle.
 * allocator has allocator_acquire, allocator_release and allocator, we could pass the above 
 * three functions to any where that needs a pf_alloc, pf_dealloc and a heap handler.
 */

/* allocator methods */
extern inline void  allocator_join     (allocator o); 
#ifdef _VERBOSE_ALLOC_DEALLOC_
extern inline void* allocator_acquire_v(allocator o, int size, const char* file, int line);
extern inline bool  allocator_release_v(allocator o, void* buff, const char* file, int line);
#define allocator_acquire allocator_acquire_v
#define allocator_release allocator_release_v
#else 
extern inline void* allocator_acquire_c(allocator o, int size);
extern inline bool  allocator_release_c(allocator o, void* buff);
#define allocator_acquire allocator_acquire_c
#define allocator_release allocator_release_c
#endif
extern inline allocator allocator_get_parent(allocator o);
extern inline void      allocator_walk      (allocator o, pf_process_block per_block_cb, void* param);

#define allocator_alloc(o, size)   alloc(allocator_acquire, o, size)
#define allocator_dealloc(o, buff) dealloc(allocator_release, o, buff)

/* system default allocator, which can not be spawned or joined */
extern allocator __global_sysd_allocator;
extern allocator __global_llrb_allocator;
extern allocator __global_buddy_allocator;

extern allocator __global_default_allocator;

/* the factory methods */
allocator allocator_llrb_spawn (allocator parent);

allocator allocator_buddy_spawn(allocator parent);

allocator allocator_spool_spawn(allocator parent);

allocator allocator_mpool_spawn(allocator parent, int max_diff_types);

#endif /* _OBJECT_ALLOCATOR_H_ */
