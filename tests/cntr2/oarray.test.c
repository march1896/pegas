#include <stdio.h>
#include <string.h>

#include "cntr2/iobject.h"
#include "cntr2/iarray.h"
#include "cntr2/iqueue.h"
#include "cntr2/istack.h"
#include "cntr2/ifactory.h"

#include "test_util.h"
#include "cntr2/iarray.test.h"
#include "cntr2/iqueue.test.h"
#include "cntr2/istack.test.h"

static void __correctness_test() {
	{
		array_test_basic();
	}
	
	{
		iqueue queue = cntr_create_oarray(int_traits);
		queue_test_basic(queue);
		iobject_destroy(queue);
	}	

	{
		istack stack = cntr_create_oarray(int_traits);
		stack_test_basic(stack);
		iobject_destroy(stack);
	}	
}

static void __performance_test() {
	log_printline("add find remove performance test start");
	log_printline("add find remove performance test end");
}

void cntr2_oarray_test() {
	test_run_single("cntr cntr_base correctness", __correctness_test);

	test_run_bench("cntr cntr_base performance", __performance_test);
}
