#include <stdio.h>
#include <string.h>

#include "cntr2/iobject.h"
#include "cntr2/ilist.h"
#include "cntr2/iqueue.h"
#include "cntr2/istack.h"
#include "cntr2/ifactory.h"

#include "ele.data.h"
#include "test_util.h"
#include "cntr2/ilist.test.h"
#include "cntr2/iqueue.test.h"
#include "cntr2/istack.test.h"

static void __correctness_test() {
	{
		Object* a = cntr_create_olist(&int_traits);
		list_test_basic(a, int_repo, &int_traits);
		iobject_destroy(a);

		a = cntr_create_olist(&longint_traits);
		list_test_basic(a, longint_repo, &longint_traits);
		iobject_destroy(a);

		a = cntr_create_olist(&float_traits);
		list_test_basic(a, float_repo, &float_traits);
		iobject_destroy(a);

		a = cntr_create_olist(&double_traits);
		list_test_basic(a, double_repo, &double_traits);
		iobject_destroy(a);

		a = cntr_create_olist(&char_traits);
		list_test_basic(a, char_repo, &char_traits);
		iobject_destroy(a);

		a = cntr_create_olist(&string_traits);
		list_test_basic(a, string_repo, &string_traits);
		iobject_destroy(a);
	}
	
	{
		Object* a = cntr_create_oarray(&int_traits);
		queue_test_basic(a, int_repo, &int_traits);
		iobject_destroy(a);

		a = cntr_create_oarray(&double_traits);
		queue_test_basic(a, double_repo, &double_traits);
		iobject_destroy(a);

		a = cntr_create_oarray(&char_traits);
		queue_test_basic(a, char_repo, &char_traits);
		iobject_destroy(a);

		a = cntr_create_oarray(&string_traits);
		queue_test_basic(a, string_repo, &string_traits);
		iobject_destroy(a);
	}	

	{
		Object* a = cntr_create_oarray(&int_traits);
		stack_test_basic(a, int_repo, &int_traits);
		iobject_destroy(a);

		a = cntr_create_oarray(&double_traits);
		stack_test_basic(a, double_repo, &double_traits);
		iobject_destroy(a);

		a = cntr_create_oarray(&char_traits);
		stack_test_basic(a, char_repo, &char_traits);
		iobject_destroy(a);

		a = cntr_create_oarray(&string_traits);
		stack_test_basic(a, string_repo, &string_traits);
		iobject_destroy(a);
	}	
}

static void __performance_test() {
	log_printline("add find remove performance test start");
	log_printline("add find remove performance test end");
}

void cntr2_odlist_test() {
	test_run_single("cntr cntr_base correctness", __correctness_test);

	test_run_bench("cntr cntr_base performance", __performance_test);
}
