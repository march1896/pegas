#include <cntr2/iset.h>
#include <cntr2/iitr.h>
#include <cntr2/ialgo.h>

#include "imset.test.h"
#include "test_util.h"

struct counter_t {
	int count; /* count of element */
	int sum;   /* sum of all element */
};
static void foreach_count(const void* __ref, void* param) {
	struct counter_t* counter = (struct counter_t*)param;

	counter->count ++;
	counter->sum += *(int*)__ref;
}

static void mset_test_basic_itr_operation(object mset) {
	int temp_int;
	imset_clear(mset);
	dbg_assert(imset_empty(mset));

	temp_int = 4;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 4);
	temp_int = 1;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 3;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 2;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 2;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 3;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 1;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 4;
	imset_insert(mset, &temp_int);
	dbg_assert(temp_int == 4);
	/* now the mset contains { 1, 1, 2, 2, 3, 3, 4, 4 } */

	dbg_assert(imset_size(mset) == 8);
	{
		iterator itr   = imset_itr_create(mset, itr_begin);
		iterator lower = imset_itr_create(mset, itr_begin);
		iterator upper = imset_itr_create(mset, itr_begin);
		struct counter_t counter;
		const_iterator end = imset_itr_end(mset);
		intptr_t current = 1;

		/* traverse the mset */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			dbg_assert(*(int*)itr_get_ref(itr) == ((current+1)/2));
			current ++;
		}

		/* test itr_assign */
		imset_itr_assign(mset, itr, itr_begin);
		dbg_assert(*(int*)itr_get_ref(itr) == 1);
		imset_itr_assign(mset, itr, itr_end);
		itr_to_prev(itr);
		dbg_assert(*(int*)itr_get_ref(itr) == 4);

		/* test itr_find_lower, itr_find_upper */
		/* find element not int the mset */
		temp_int = 0;
		imset_itr_find_lower(mset, lower, &temp_int);
		dbg_assert(temp_int == 0);
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(temp_int == 0);
		/* NOTE: we will not find the end of the set */
		/* dbg_assert(itr_equals(lower, imset_itr_end(mset))); */
		dbg_assert(itr_equals(upper, lower));
		dbg_assert(itr_equals(lower, imset_itr_begin(mset)));

		/* test itr_find_lower, itr_find_upper */
		/* find element not int the mset */
		temp_int = 5;
		imset_itr_find_lower(mset, lower, &temp_int);
		dbg_assert(temp_int == 5);
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(temp_int == 5);
		/* NOTE: we will not find the end of the set */
		/* dbg_assert(itr_equals(lower, imset_itr_end(mset))); */
		dbg_assert(itr_equals(upper, lower));
		dbg_assert(itr_equals(lower, imset_itr_end(mset)));

		temp_int = 1;
		imset_itr_find_lower(mset, lower, &temp_int);
		dbg_assert(temp_int == 1);
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(temp_int == 1);
		dbg_assert(!itr_equals(lower, upper));
		counter.count = 0;
		counter.sum = 0;
		foreach_v(lower, upper, foreach_count, &counter);
		dbg_assert(counter.count == 2);
		dbg_assert(counter.sum == 2);

		temp_int = 3;
		imset_itr_find_lower(mset, lower, &temp_int);
		dbg_assert(temp_int == 3);
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(temp_int == 3);
		dbg_assert(!itr_equals(lower, upper));
		counter.count = 0;
		counter.sum = 0;
		foreach_v(lower, upper, foreach_count, &counter);
		dbg_assert(counter.count == 2);
		dbg_assert(counter.sum == 6);

		temp_int = 1;
		imset_itr_find_lower(mset, lower, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 3;
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(temp_int == 3);
		dbg_assert(!itr_equals(lower, upper));
		counter.count = 0;
		counter.sum = 0;
		foreach_v(lower, upper, foreach_count, &counter);
		dbg_assert(counter.count == 6);
		dbg_assert(counter.sum == 12); /* 1 + 1 + 2 + 2 + 3 + 3  */

		/* test itr_remove */
		temp_int = 2;
		imset_itr_find_lower(mset, itr, &temp_int);
		dbg_assert(temp_int == 2);
		dbg_assert(!itr_equals(itr, imset_itr_end(mset)));

		imset_itr_remove(mset, itr);
		/* now the mset is { 1, 1, 2,  3, 3, 4, 4 } */
		dbg_assert(imset_size(mset) == 7);
		temp_int = 2;
		imset_itr_find_lower(mset, lower, &temp_int);
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(!itr_equals(lower, upper));
		counter.count = 0;
		counter.sum = 0;
		foreach_v(lower, upper, foreach_count, &counter);
		dbg_assert(counter.count == 1);
		dbg_assert(counter.sum == 2);

		temp_int = 1;
		imset_itr_find_lower(mset, lower, &temp_int);
		temp_int = 3;
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(!itr_equals(lower, upper));
		counter.count = 0;
		counter.sum = 0;
		foreach_v(lower, upper, foreach_count, &counter);
		dbg_assert(counter.count == 5);
		dbg_assert(counter.sum == 10); /* 1 + 1 + 2 + 3 + 3  */

		/* test continuous itr_remove */
		temp_int = 2;
		imset_itr_find_lower(mset, itr, &temp_int);
		dbg_assert(!itr_equals(itr, imset_itr_end(mset)));

		imset_itr_remove(mset, itr);
		/* now the mset is { 1, 1, 3, 3, 4, 4 } */
		dbg_assert(imset_size(mset) == 6);
		temp_int = 2;
		imset_itr_find_lower(mset, lower, &temp_int);
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(itr_equals(lower, upper));
		temp_int = 3;
		imset_itr_find_lower(mset, upper, &temp_int);
		dbg_assert(itr_equals(lower, upper));
		counter.count = 0;
		counter.sum = 0;
		foreach_v(lower, upper, foreach_count, &counter);
		dbg_assert(counter.count == 0);
		dbg_assert(counter.sum == 0);

		temp_int = 1;
		imset_itr_find_lower(mset, lower, &temp_int);
		temp_int = 2;
		imset_itr_find_upper(mset, upper, &temp_int);
		dbg_assert(!itr_equals(lower, upper));
		counter.count = 0;
		counter.sum = 0;
		foreach_v(lower, upper, foreach_count, &counter);
		dbg_assert(counter.count == 2);
		dbg_assert(counter.sum == 2); /* 1 + 1 */

		itr_destroy(itr);
		itr_destroy(lower);
		itr_destroy(upper);
	}

	return;
}

static void mset_test_basic_operation(object mset) {
	int temp_int = 0;
	imset_clear(mset);
	dbg_assert(imset_empty(mset));

	{
		temp_int = 4;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 4);
		temp_int = 1;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 3;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 3);
		temp_int = 2;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 2);
		temp_int = 2;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 2);
		temp_int = 3;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 3);
		temp_int = 1;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 4;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 4);
	}
	/* now the mset contains { 1, 1, 2, 2, 3, 3, 4, 4 } */
	dbg_assert(imset_size(mset) == 8);
	{
		intptr_t current = 1;

		temp_int = 0;
		dbg_assert(imset_contains(mset, &temp_int) == false);
		dbg_assert(temp_int == 0);
		temp_int = 5;
		dbg_assert(imset_contains(mset, &temp_int) == false);
		dbg_assert(temp_int == 5);

		for (current = 1; current <= 4; current ++) {
			dbg_assert(imset_contains(mset, &current) == true);
			dbg_assert(imset_count(mset, &current) == 2);
		}
	}

	/* test remove, delete the even ones */
	dbg_assert(imset_size(mset) == 8);
	dbg_assert(imset_empty(mset) == false);
	{
		/* now the mset contains { 1, 1, 2, 2, 3, 3, 4, 4 } */
		int count;

		temp_int = 2;
		count = imset_remove(mset, &temp_int);
		/* now the mset contains { 1, 1, 3, 3, 4, 4 } */
		dbg_assert(count == 2);
		dbg_assert(imset_size(mset) == 6);
		temp_int = 2;
		dbg_assert(imset_contains(mset, &temp_int) == false);
		dbg_assert(temp_int == 2);
		dbg_assert(imset_count(mset, &temp_int) == 0);

		dbg_assert(temp_int == 2);
		count = imset_remove(mset, &temp_int);
		/* now the mset contains { 1, 1,  3, 3, 4, 4 } */
		dbg_assert(count == 0);
		dbg_assert(imset_size(mset) == 6);
		temp_int = 2;
		dbg_assert(imset_contains(mset, &temp_int) == false);
		dbg_assert(temp_int == 2);
		dbg_assert(imset_count(mset, &temp_int) == 0);

		/* try to remove element not in mset */
		dbg_assert(temp_int == 2);
		count = imset_remove(mset, &temp_int);
		/* now the mset contains { 1, 1,  3, 3, 4, 4 } */
		dbg_assert(count == 0);
		dbg_assert(imset_size(mset) == 6);
		temp_int = 2;
		dbg_assert(imset_contains(mset, &temp_int) == false);
		dbg_assert(temp_int == 2);
		dbg_assert(imset_count(mset, &temp_int) == 0);

		temp_int = 3;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 3);
		/* now the mset contains { 1, 1, 3, 3, 3, 4, 4 } */
		dbg_assert(imset_size(mset) == 7);
		temp_int = 2;
		dbg_assert(imset_contains(mset, &temp_int) == false);
		dbg_assert(temp_int == 2);
		temp_int = 3;
		dbg_assert(imset_contains(mset, &temp_int) == true);
		dbg_assert(temp_int == 3);
		dbg_assert(imset_count(mset, &temp_int) == 3);
		dbg_assert(temp_int == 3);
	}

	dbg_assert(imset_size(mset) == 7);

	/* test clear */
	{
		imset_clear(mset);
		/* now the mset is empty */
		dbg_assert(imset_empty(mset));
		
		/* clear an empty mset */
		imset_clear(mset);
		dbg_assert(imset_empty(mset));

		temp_int = 1;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 1;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 1;
		imset_insert(mset, &temp_int);
		dbg_assert(temp_int == 1);

		/* now the mset is { 1, 1, 1 } */
		imset_clear(mset);
		dbg_assert(imset_empty(mset));
	}
}

static int __num_modify; /* number of insert and remove */
static int __num_search;

static int __data_diff_type; /* number of different values to store in the mset */
static int __data_max_count; /* max count of a single value */

static object __mset = NULL; /* to be tested */
static intptr_t* data_count = NULL;

static void __reset_data() {
	int i = 0;

	for (i = 0; i < __data_diff_type; i ++) {
		data_count[i] = 0;
	}
}

static void __create_data() {
	if (data_count != NULL) 
		free(data_count);

	data_count = (intptr_t*)malloc(sizeof(intptr_t)*__data_diff_type);

	__reset_data();
}

static void __destroy_data() {
	free(data_count);
	data_count = NULL;
}

static void mset_bench_modify_randomly() {
	int i;

	log_printline("[number of modify: %d]", __num_modify);
	dbg_assert(imset_empty(__mset));

	for (i = 0; i < __num_modify; i ++) {
		intptr_t x = rand() % __data_diff_type;
		int count = imset_count(__mset, &x);
		
		if (count == 0) {
			imset_insert(__mset, &x);
			data_count[x] ++;
		} else if (count == __data_max_count) {
			imset_remove(__mset, &x);
			data_count[x] --;
		} else {
			int addit = rand() % 2;
			if (addit == 1) {
				imset_insert(__mset, &x);
				data_count[x] ++;
			}
			else {
				bool res = imset_remove(__mset, &x);
				dbg_assert(res == true);
				imset_remove(__mset, &x);
			}
		}
	}

	imset_clear(__mset);
}

static void mset_bench_search_randomly() {
	int i;
	dbg_assert(imset_empty(__mset));

	log_printline("[number of search: %d]", __num_search);

	for (i = 0; i < __data_diff_type; i ++) {
		intptr_t x = rand() % __data_diff_type;
		/* insert all data one by one */
		imset_insert(__mset, &i);
		/* insert some data randomly */
		imset_insert(__mset, &x);
	}
	/* now the mset contains __data_diff_type * 2 of data, each elememt int [0, __data_diff_type)
	 * appears at least once */

	for (i = 0; i < __num_search; i ++) {
		intptr_t x = rand() % __data_diff_type;

		bool res = imset_contains(__mset, &x);
		dbg_assert(res == true);
	}

	imset_clear(__mset);
}

void mset_test_basic(object mset) {
	mset_test_basic_operation(mset);
	mset_test_basic_itr_operation(mset);
}

void mset_test_memory(object mset) {
}

void mset_test_bench(object mset) {
	__mset = mset;
	__data_diff_type = 100;
	__data_max_count = 10;
	__num_modify     = 100;
	__num_search     = 100;
	imset_clear(__mset);
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	
	__create_data();
	test_run_single("randomly modify test", mset_bench_modify_randomly);
	__destroy_data();
	test_run_single("randomly search test", mset_bench_search_randomly);

	__num_modify     = 100000;
	__num_search     = 100;
	__create_data();
	test_run_single("randomly modify test", mset_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 100000;
	test_run_single("randomly search test", mset_bench_search_randomly);

	__data_diff_type = 5000;
	__data_max_count = 10;
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	__num_modify     = 100000;
	__num_search     = 100;
	__create_data();
	test_run_single("randomly modify test", mset_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 100000;
	test_run_single("randomly search test", mset_bench_search_randomly);

	__data_diff_type = 100000;
	__data_max_count = 10;
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	__num_modify     = 100000;
	__num_search     = 100;

	__create_data();
	test_run_single("randomly modify test", mset_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 100000;
	test_run_single("randomly search test", mset_bench_search_randomly);

	__data_diff_type = 100000;
	__data_max_count = 10;
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	__num_modify     = 10000000;
	__num_search     = 100;

	__create_data();
	test_run_single("randomly modify test", mset_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 10000000;
	test_run_single("randomly search test", mset_bench_search_randomly);
}
