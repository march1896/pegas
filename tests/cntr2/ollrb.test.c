#include <cntr2/iobject.h>
#include <cntr2/iset.h>
#include <cntr2/ifactory.h>
#include <cntr2/oallocator.h>

#include "ele.data.h"
#include "test_util.h"
#include "cntr2/iset.test.h"
#include "cntr2/imset.test.h"

static void __as_set_basic_test() {
	Object* a;
	a = cntr_create_ollrb(&int_traits);
	set_test_basic(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&longint_traits);
	set_test_basic(a, longint_repo, &longint_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&float_traits);
	set_test_basic(a, float_repo, &float_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&double_traits);
	set_test_basic(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&char_traits);
	set_test_basic(a, char_repo, &char_traits);
	iobject_destroy(a);

 	a = cntr_create_ollrb(&string_traits);
	set_test_basic(a, string_repo, &string_traits);
	iobject_destroy(a);
}

static void __as_mset_basic_test() {
	Object* a = cntr_create_ollrb(&int_traits);
	mset_test_basic(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&longint_traits);
	mset_test_basic(a, longint_repo, &longint_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&float_traits);
	mset_test_basic(a, float_repo, &float_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&double_traits);
	mset_test_basic(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&char_traits);
	mset_test_basic(a, char_repo, &char_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&string_traits);
	mset_test_basic(a, string_repo, &string_traits);
	iobject_destroy(a);
}

static void __as_set_bench_test() {
	Object* a = cntr_create_ollrb_a(&int_traits, NULL);
	set_test_bench(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb_a(&double_traits, NULL);
	set_test_bench(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&string_traits);
	set_test_bench(a, string_repo, &string_traits);
	iobject_destroy(a);
}

static void __as_mset_bench_test() {
	Object* a = cntr_create_ollrb_a(&int_traits, NULL);
	mset_test_bench(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb_a(&double_traits, NULL);
	mset_test_bench(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_ollrb(&string_traits);
	mset_test_bench(a, string_repo, &string_traits);
	iobject_destroy(a);
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
