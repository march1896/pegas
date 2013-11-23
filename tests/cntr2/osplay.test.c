#include <cntr2/iobject.h>
#include <cntr2/iset.h>
#include <cntr2/ifactory.h>

#include "ele.data.h"
#include "test_util.h"
#include "cntr2/iset.test.h"
#include "cntr2/imset.test.h"

static void __as_set_basic_test() {
	Object* a = cntr_create_osplay(&int_traits);
	set_test_basic(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&longint_traits);
	set_test_basic(a, longint_repo, &longint_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&float_traits);
	set_test_basic(a, float_repo, &float_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&double_traits);
	set_test_basic(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&char_traits);
	set_test_basic(a, char_repo, &char_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&string_traits);
	set_test_basic(a, string_repo, &string_traits);
	iobject_destroy(a);
}

static void __as_mset_basic_test() {
	Object* a = cntr_create_osplay(&int_traits);
	mset_test_basic(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&longint_traits);
	mset_test_basic(a, longint_repo, &longint_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&float_traits);
	mset_test_basic(a, float_repo, &float_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&double_traits);
	mset_test_basic(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&char_traits);
	mset_test_basic(a, char_repo, &char_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&string_traits);
	mset_test_basic(a, string_repo, &string_traits);
	iobject_destroy(a);
}

static void __as_set_bench_test() {
	Object* a = cntr_create_osplay_a(&int_traits, NULL);
	set_test_bench(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_osplay_a(&double_traits, NULL);
	set_test_bench(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&string_traits);
	set_test_bench(a, string_repo, &string_traits);
	iobject_destroy(a);
}

static void __as_mset_bench_test() {
	Object* a = cntr_create_osplay_a(&int_traits, NULL);
	mset_test_bench(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_osplay_a(&double_traits, NULL);
	mset_test_bench(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_osplay(&string_traits);
	mset_test_bench(a, string_repo, &string_traits);
	iobject_destroy(a);
}

static void __correctness_test() {
	test_run_single("osplay as set basic test", __as_set_basic_test);
	test_run_single("osplay as mset basic test", __as_mset_basic_test);
}

static void __performance_test() {
	test_run_single("osplay as set bench test", __as_set_bench_test);
	test_run_single("osplay as mset bench test", __as_mset_bench_test);
}

void cntr2_osplay_test() {
	test_run_single("cntr_splay correctness", __correctness_test);

	test_run_bench("cntr_splay performance", __performance_test);
}
