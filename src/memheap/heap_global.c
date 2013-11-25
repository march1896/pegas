#include <memheap/heap_global.h>

#include <memheap/heap_sys.h>
#include <memheap/heap_llrb.h>
#include <memheap/heap_wrap.h>
#include <memheap/heap_buddy.h>

#include <memheap/heap_factory.h>

void*      __global_sysd_heap  = NULL;
pf_alloc   __global_sysd_alloc = (pf_alloc)heap_sysd_alloc;
pf_dealloc __global_sysd_dealloc = (pf_dealloc)heap_sysd_dealloc;

struct heap_llrb __global_static_heap_llrb = {
	NULL,                /* parent */
	heap_sysd_alloc,     /* alloc  */
	heap_sysd_dealloc,   /* dealloc */
	NULL,                /* llrb_root */
	{
		&(__global_static_heap_llrb.memlist),
		&(__global_static_heap_llrb.memlist)
	},                   /* mem_list */
	sizeof(struct heap_llrb_block),  /* split_threshold */
	HEAP_MINIMUM_EXPAND_SIZE         /* expand_size */
};

void*      __global_llrb_heap    = (void*)&__global_static_heap_llrb;
pf_alloc   __global_llrb_alloc   = (pf_alloc)heap_llrb_alloc;
pf_dealloc __global_llrb_dealloc = (pf_dealloc)heap_llrb_dealloc;

#define list_static_init(var) {&var, &var}

struct heap_buddy __global_static_heap_buddy = {
	NULL,                /* parent */
	heap_sysd_alloc,     /* alloc  */
	heap_sysd_dealloc,   /* dealloc */
	{
		/* is there a better way ? */
		list_static_init(__global_static_heap_buddy.buddy[0]),
		list_static_init(__global_static_heap_buddy.buddy[1]),
		list_static_init(__global_static_heap_buddy.buddy[2]),
		list_static_init(__global_static_heap_buddy.buddy[3]),
		list_static_init(__global_static_heap_buddy.buddy[4]),
		list_static_init(__global_static_heap_buddy.buddy[5]),
		list_static_init(__global_static_heap_buddy.buddy[6]),
		list_static_init(__global_static_heap_buddy.buddy[7]),
		list_static_init(__global_static_heap_buddy.buddy[8]),
		list_static_init(__global_static_heap_buddy.buddy[9]),
		list_static_init(__global_static_heap_buddy.buddy[10]),
		list_static_init(__global_static_heap_buddy.buddy[11]),
		list_static_init(__global_static_heap_buddy.buddy[12]),
		list_static_init(__global_static_heap_buddy.buddy[13]),
		list_static_init(__global_static_heap_buddy.buddy[14]),
		list_static_init(__global_static_heap_buddy.buddy[15]),
		list_static_init(__global_static_heap_buddy.buddy[16]),
		list_static_init(__global_static_heap_buddy.buddy[17]),
		list_static_init(__global_static_heap_buddy.buddy[18]),
		list_static_init(__global_static_heap_buddy.buddy[19]),
		list_static_init(__global_static_heap_buddy.buddy[20]),
		list_static_init(__global_static_heap_buddy.buddy[21]),
		list_static_init(__global_static_heap_buddy.buddy[22]),
		list_static_init(__global_static_heap_buddy.buddy[23]),
		list_static_init(__global_static_heap_buddy.buddy[24]),
		list_static_init(__global_static_heap_buddy.buddy[25]),
		list_static_init(__global_static_heap_buddy.buddy[26]),
		list_static_init(__global_static_heap_buddy.buddy[27]),
		list_static_init(__global_static_heap_buddy.buddy[28]),
		list_static_init(__global_static_heap_buddy.buddy[29]),
		list_static_init(__global_static_heap_buddy.buddy[30]),
		list_static_init(__global_static_heap_buddy.buddy[31])
	},                   /* buddy[BUDDY_COUNT] */
	{
		&(__global_static_heap_buddy.memlist),
		&(__global_static_heap_buddy.memlist)
	},                   /* mem_list */
	sizeof(struct heap_buddy_block),  /* split_threshold */
	HEAP_MINIMUM_EXPAND_SIZE         /* expand_size */
};

void*      __global_buddy_heap    = (void*)&__global_static_heap_buddy;
pf_alloc   __global_buddy_alloc   = (pf_alloc)heap_buddy_alloc;
pf_dealloc __global_buddy_dealloc = (pf_dealloc)heap_buddy_dealloc;

void*      __global_default_heap    = (void*)&__global_static_heap_buddy;;
pf_alloc   __global_default_alloc   = (pf_alloc)heap_buddy_alloc;
pf_dealloc __global_default_dealloc = (pf_dealloc)heap_buddy_dealloc;
