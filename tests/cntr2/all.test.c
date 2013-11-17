#include "memheap/heap_global.h"
#include "cntr2/oallocator.h"

#include "test_util.h"

extern void cntr2_oallocator_test();
extern void cntr2_odlist_test();
extern void cntr2_ollrb_test();
extern void cntr2_osplay_test();
extern void cntr2_oskiplist_test();

void cntr2_all_test() {
	test_run_single("allocator object test", cntr2_oallocator_test);
	//allocator_walk(__global_default_allocator, allocator_heap_walk_print, NULL);

	test_run_single("dlist object test", cntr2_odlist_test);
	//allocator_walk(__global_default_allocator, allocator_heap_walk_print, NULL);

	test_run_single("ollrb object test", cntr2_ollrb_test);
	//allocator_walk(__global_default_allocator, allocator_heap_walk_print, NULL);

	test_run_single("osplay object test", cntr2_osplay_test);
	//allocator_walk(__global_default_allocator, allocator_heap_walk_print, NULL);

	//test_run_single("oskiplist object test", cntr2_oskiplist_test);

	/* check the container/iterator memory leak */
	allocator_walk(__global_default_allocator, allocator_heap_walk_print, NULL);
}
