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
	test_run_single_v("int", (pf_test_case_v)set_test_basic, a, &int_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&longint_traits);
	test_run_single_v("longint", (pf_test_case_v)set_test_basic, a, &longint_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&float_traits);
	test_run_single_v("float", (pf_test_case_v)set_test_basic, a, &float_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&double_traits);
	test_run_single_v("double", (pf_test_case_v)set_test_basic, a, &double_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&char_traits);
	test_run_single_v("char", (pf_test_case_v)set_test_basic, a, &char_test_desc);
	iobject_destroy(a);

 	a = cntr_create_ollrb(&string_traits);
	test_run_single_v("string", (pf_test_case_v)set_test_basic, a, &string_test_desc);
	iobject_destroy(a);
}

static void __as_mset_basic_test() {
	Object* a = cntr_create_ollrb(&int_traits);
	test_run_single_v("int", (pf_test_case_v)mset_test_basic, a, &int_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&longint_traits);
	test_run_single_v("longint", (pf_test_case_v)mset_test_basic, a, &longint_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&float_traits);
	test_run_single_v("float", (pf_test_case_v)mset_test_basic, a, &float_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&double_traits);
	test_run_single_v("double", (pf_test_case_v)mset_test_basic, a, &double_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&char_traits);
	test_run_single_v("char", (pf_test_case_v)mset_test_basic, a, &char_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&string_traits);
	test_run_single_v("string", (pf_test_case_v)mset_test_basic, a, &string_test_desc);
	iobject_destroy(a);
}

static void __as_set_bench_test() {
	Object* a = cntr_create_ollrb_a(&int_traits, NULL);
	test_run_bench_v("int", (pf_test_case_v)set_test_bench, a, &int_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb_a(&double_traits, NULL);
	test_run_bench_v("double", (pf_test_case_v)set_test_bench, a, &double_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&string_traits);
	test_run_bench_v("string", (pf_test_case_v)set_test_bench, a, &string_test_desc);
	iobject_destroy(a);
}

static void __as_mset_bench_test() {
	Object* a = cntr_create_ollrb_a(&int_traits, NULL);
	test_run_bench_v("int", (pf_test_case_v)mset_test_bench, a, &int_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb_a(&double_traits, NULL);
	test_run_bench_v("double", (pf_test_case_v)mset_test_bench, a, &double_test_desc);
	iobject_destroy(a);

	a = cntr_create_ollrb(&string_traits);
	test_run_bench_v("string", (pf_test_case_v)mset_test_bench, a, &string_test_desc);
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
