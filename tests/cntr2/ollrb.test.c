#include <cntr2/iobject.h>
#include <cntr2/iset.h>
#include <cntr2/ifactory.h>
#include <cntr2/oallocator.h>

#include "test_util.h"
#include "cntr2/iset.test.h"
#include "cntr2/imset.test.h"

static int int_compare(const void* a, const void* b) {
	if ((intptr_t)a < (intptr_t)b) {
		return -1;
	}
	else if ((intptr_t)a > (intptr_t)b) {
		return 1;
	}
	return 0;
}

static void __as_set_basic_test() {
	iset set = cntr_create_ollrb(int_traits);
	set_test_basic(set);
	iobject_destroy(set);
}

static void __as_mset_basic_test() {
	imset mset = cntr_create_ollrb(int_traits);
	mset_test_basic(mset);
	iobject_destroy(mset);
}

static void __as_set_bench_test() {
	iset set = cntr_create_ollrb_a(int_traits, NULL);
	set_test_bench(set);
	iobject_destroy(set);
}

static void __as_mset_bench_test() {
	imset mset = cntr_create_ollrb_a(int_traits, NULL);
	mset_test_bench(mset);
	iobject_destroy(mset);
}

static void __correctness_test() {
	test_run_single("ollrb as set basic test", __as_set_basic_test);
	test_run_single("ollrb as mset basic test", __as_mset_basic_test);
}

static void __performance_test() {
	test_run_single("ollrb as set bench test", __as_set_bench_test);
	test_run_single("ollrb as mset bench test", __as_mset_bench_test);
}

void cntr2_ollrb_test() {
	test_run_single("cntr_llrb correctness", __correctness_test);

	test_run_bench("cntr_llrb performance", __performance_test);
}
