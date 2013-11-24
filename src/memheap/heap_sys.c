#include <util/cominc.h>
#include <memheap/heap_def.h>

#include <stdlib.h>

void* heap_sysd_alloc_c(void* h, int size) {
	unused(h);

	return malloc(size);
}

void* heap_sysd_alloc_v(void* h, int size, const char* file ,int line) {
	unused(h);
	unused(file);
	unused(line);

	return malloc(size);
}

bool heap_sysd_dealloc_c(void* h, void* buff) {
	/* we can not handle the system heap, the only way to use it is globally */
	unused(h);

	free(buff);

	return true;
}

bool heap_sysd_dealloc_v(void* h, void* buff, const char* file, int line) {
	unused(h);
	unused(file);
	unused(line);

	free(buff);

	return true;
}
