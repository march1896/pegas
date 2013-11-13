#include <cntr2/oo_ref.h>


void* pointer_clone_v(const_unknown __ref, pf_alloc alc, void* heap) {
	unused(alc);
	unused(heap);

	return (void*)__ref;
}
void  pointer_destroy_v(unknown __ref, pf_dealloc dlc, void* heap) {
	unused(__ref);
	unused(dlc);
	unused(heap);
}
bool  pointer_equals_v(const_unknown ref_a, const_unknown ref_b, void* context) {
	unused(context);
	return ref_a == ref_b;
}
