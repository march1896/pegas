#include <cntr2/oo_bridge.h>
#include <memheap/heap_def.h>

static unknown *pointer_clone(const unknown* ref_x, pf_alloc alc, void* heap) {
	/* just return the reference that ref_x points to */
	return (unknown*)ref_x;
}
static void pointer_destroy(const unknown* ref_x, pf_dealloc dlc, void* heap) {
	/* no need to destroy */
}
static compres pointer_compare_to(const unknown* ref_x, const unknown* ref_y) {
	/* just use the address to compare */
	if (ref_x < ref_y) 
		return -1;
	else if (ref_x > ref_y) 
		return 1;
	return 0;
}
static bool pointer_equals(const unknown* ref_x, const unknown* ref_y) {
	/* just use the address to compare */
	return ref_x == ref_y;
}
static hashcode pointer_hashcode(const unknown* ref_x) {
	// TODO
	return (hashcode)ref_x;
}
unknown_traits pointer_traits = {
	pointer_destroy,
	pointer_clone,
	pointer_compare_to,
	pointer_equals,
	pointer_hashcode
};

static unknown *int_clone(const unknown* ref_x, pf_alloc alc, void* heap) {
	int* new_int = (int*)alloc(alc, heap, sizeof(int));
	*new_int = *(int*)ref_x;
	return (unknown*)new_int;
}
static void int_destroy(const unknown* ref_x, pf_dealloc dlc, void* heap) {
	dealloc(dlc, heap, (void*)ref_x);
}
static compres int_compare_to(const unknown* ref_x, const unknown* ref_y) {
	int x = *(int*)ref_x;
	int y = *(int*)ref_y;

	if (x < y) 
		return -1;
	else if (x > y) 
		return 1;
	return 0;
}
static bool int_equals(const unknown* ref_x, const unknown* ref_y) {
	int x = *(int*)ref_x;
	int y = *(int*)ref_y;
	return x == y;
}
static hashcode int_hashcode(const unknown* ref_x) {
	// TODO
	return (hashcode)(*(int*)ref_x);
}
unknown_traits int_traits = {
	int_destroy,
	int_clone,
	int_compare_to,
	int_equals,
	int_hashcode
};

