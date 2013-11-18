#include "cntr2/iset.h"
#include "cntr2/iitr.h"

#include "iset.test.h"
#include "test_util.h"

static void set_test_basic_itr_operation(object set) {
	int temp_int = 0;
	iset_clear(set);
	dbg_assert(iset_empty(set));

	temp_int = 4;
	iset_insert(set, &temp_int);
	temp_int = 5;
	iset_insert(set, &temp_int);
	temp_int = 3;
	iset_insert(set, &temp_int);
	temp_int = 6;
	iset_insert(set, &temp_int);
	temp_int = 2;
	iset_insert(set, &temp_int);
	temp_int = 7;
	iset_insert(set, &temp_int);
	temp_int = 1;
	iset_insert(set, &temp_int);
	temp_int = 8;
	iset_insert(set, &temp_int);
	/* now the set contains { 1, 2, 3, 4, 5, 6, 7, 8 } */

	dbg_assert(iset_size(set) == 8);
	{
		iterator itr = iset_itr_create(set, itr_begin);
		const_iterator end = iset_itr_end(set);
		intptr_t current = 1;

		/* traverse the set */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			dbg_assert(*(int*)itr_get_ref(itr) == current);
			current ++;
		}

		/* test itr_assign */
		iset_itr_assign(set, itr, itr_begin);
		dbg_assert(*(int*)itr_get_ref(itr) == 1);
		iset_itr_assign(set, itr, itr_end);
		itr_to_prev(itr);
		dbg_assert(*(int*)itr_get_ref(itr) == 8);

		/* test itr_find */
		temp_int = 0;
		iset_itr_find(set, itr, &temp_int);
		dbg_assert(itr_equals(itr, iset_itr_end(set)));
		temp_int = 9;
		iset_itr_find(set, itr, &temp_int);
		dbg_assert(itr_equals(itr, iset_itr_end(set)));

		for (current = 1; current <= 8; current ++) {
			iset_itr_find(set, itr, &current);
			dbg_assert(!itr_equals(itr, iset_itr_end(set)));
		}

		/* test itr_remove */
		temp_int = 4;
		iset_itr_find(set, itr, &temp_int);
		dbg_assert(!itr_equals(itr, iset_itr_end(set)));

		iset_itr_remove(set, itr);
		/* now the set is { 1, 2, 3,  , 5, 6, 7, 8 } */
		dbg_assert(iset_size(set) == 7);
		for (current = 0; current <= 9; current ++) {
			iset_itr_find(set, itr, &current);
			if (current == 0 || current == 9 || current == 4) {
				dbg_assert(itr_equals(itr, iset_itr_end(set)));
			}
			else {
				dbg_assert(!itr_equals(itr, iset_itr_end(set)));
			}
		}

		/* test continuous itr_remove */
		temp_int = 5;
		iset_itr_find(set, itr, &temp_int);
		dbg_assert(!itr_equals(itr, iset_itr_end(set)));

		iset_itr_remove(set, itr);
		/* now the set is { 1, 2, 3,   6, 7, 8 } */
		dbg_assert(iset_size(set) == 6);
		for (current = 0; current <= 9; current ++) {
			iset_itr_find(set, itr, &current);
			if (current == 0 || current == 9 || current == 4 || current == 5) {
				dbg_assert(itr_equals(itr, iset_itr_end(set)));
			}
			else {
				dbg_assert(!itr_equals(itr, iset_itr_end(set)));
			}
		}

		itr_destroy(itr);
	}

	return;
}

static void set_test_basic_operation(object set) {
	int temp_int;
	iset_clear(set);
	dbg_assert(iset_empty(set));

	{
		temp_int = 4;
		iset_insert(set, &temp_int);
		temp_int = 5;
		iset_insert(set, &temp_int);
		temp_int = 3;
		iset_insert(set, &temp_int);
		temp_int = 6;
		iset_insert(set, &temp_int);
		temp_int = 2;
		iset_insert(set, &temp_int);
		temp_int = 7;
		iset_insert(set, &temp_int);
		temp_int = 1;
		iset_insert(set, &temp_int);
		temp_int = 8;
		iset_insert(set, &temp_int);
	}
	/* now the set contains { 1, 2, 3, 4, 5, 6, 7, 8 } */
	dbg_assert(iset_size(set) == 8);
	{
		intptr_t current = 1;

		for (; current <= 8; current ++) {
			dbg_assert(iset_contains(set, &current));
		}
		temp_int = 0;
		dbg_assert(iset_contains(set, &temp_int) == false);
		temp_int = 9;
		dbg_assert(iset_contains(set, &temp_int) == false);
	}

	/* test remove, delete the even ones */
	dbg_assert(iset_size(set) == 8);
	{
		/* now the set contains { 1, 2, 3, 4, 5, 6, 7, 8 } */
		intptr_t x;
		bool res;

		for (x = 2; x <= 8; x +=2) {
			res = iset_remove(set, &x);
			dbg_assert(res == 1);
		}

		dbg_assert(iset_size(set) == 4);
		for (x = 1; x <= 8; x ++) {
			bool exist = x % 2 ? true : false;
			dbg_assert(iset_contains(set, &x) == exist);
		}

		temp_int = 0;
		dbg_assert(iset_contains(set, &temp_int) == false);
		temp_int = 0;
		dbg_assert(iset_contains(set, &temp_int) == false);
	}

	dbg_assert(iset_size(set) == 4);
	{
		bool bool_res = false;
		int temp_int = 0;
		void* old_ref = 0;

		/* remove elements one by one */
		temp_int = 3;
		bool_res = iset_remove(set, &temp_int);
		dbg_assert(temp_int == 3);
		/* now the set is { 1,  5, 7 } */
		dbg_assert(bool_res == true);
		dbg_assert(iset_size(set) == 3);
		dbg_assert(iset_empty(set) == false);
		dbg_assert(iset_contains(set, &temp_int) == false);

		/* try to remove another 3, should failed */
		temp_int = 3;
		bool_res = iset_remove(set, &temp_int);
		dbg_assert(temp_int == 3);
		/* now the set is { 1,  5, 7 } */
		dbg_assert(bool_res == false);
		dbg_assert(iset_size(set) == 3);
		dbg_assert(iset_empty(set) == false);
		dbg_assert(iset_contains(set, &temp_int) == false);

		temp_int = 5;
		bool_res = iset_remove(set, &temp_int);
		dbg_assert(temp_int == 5);
		/* now the set is { 1,   7 } */
		dbg_assert(bool_res == true);
		dbg_assert(iset_size(set) == 2);
		dbg_assert(iset_empty(set) == false);
		dbg_assert(iset_contains(set, &temp_int) == false);
		
		temp_int = 1;
		bool_res = iset_remove(set, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the set is { 7 } */
		dbg_assert(bool_res == true);
		dbg_assert(iset_size(set) == 1);
		dbg_assert(iset_empty(set) == false);
		dbg_assert(iset_contains(set, &temp_int) == false);

		temp_int = 7;
		bool_res = iset_remove(set, &temp_int);
		dbg_assert(temp_int == 7);
		/* now the set is { } */
		dbg_assert(bool_res == true);
		dbg_assert(iset_size(set) == 0);
		dbg_assert(iset_empty(set) == true);
		dbg_assert(iset_contains(set, &temp_int) == false);

		/* try to remove element from empty set */
		temp_int = 7;
		bool_res = iset_remove(set, &temp_int);
		dbg_assert(temp_int == 7);
		/* now the set is { } */
		dbg_assert(bool_res == false);
		dbg_assert(iset_size(set) == 0);
		dbg_assert(iset_empty(set) == true);
		dbg_assert(iset_contains(set, &temp_int) == false);

		/* trying to add element into the set after removing from empty set */
		temp_int = 2;
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 2);
		/* now the set is { 2 } */
		dbg_assert(iset_size(set) == 1);
		dbg_assert(iset_empty(set) == false);
		temp_int = 2;
		dbg_assert(iset_contains(set, &temp_int) == true);
		temp_int = 0;
		dbg_assert(iset_contains(set, &temp_int) == false);

		temp_int = 3;
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 3);
		/* now the set is { 2, 3 } */
		dbg_assert(iset_size(set) == 2);
		dbg_assert(iset_empty(set) == false);
		temp_int = 2;
		dbg_assert(iset_contains(set, &temp_int) == true);
		temp_int = 3;
		dbg_assert(iset_contains(set, &temp_int) == true);

		iset_clear(set);
	}

	dbg_assert(iset_empty(set) == true);
	{
		int temp_int = 0;
		void* old_ref = NULL;
		/* try to add same element to the set */
		temp_int = 1;
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the set is { 1 } */
		dbg_assert(iset_size(set) == 1);
		dbg_assert(iset_empty(set) == false);
		temp_int = 1;
		dbg_assert(iset_contains(set, &temp_int) == true);
		temp_int = 0;
		dbg_assert(iset_contains(set, &temp_int) == false);

		/* insert 1 again */
		temp_int = 1;
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the set is { 1 } */
		dbg_assert(iset_size(set) == 1);
		dbg_assert(iset_empty(set) == false);
		temp_int = 1;
		dbg_assert(iset_contains(set, &temp_int) == true);
		temp_int = 0;
		dbg_assert(iset_contains(set, &temp_int) == false);

		/* insert 1 again and again */
		temp_int = 1;
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the set is { 1 } */
		dbg_assert(iset_size(set) == 1);
		dbg_assert(iset_empty(set) == false);
		temp_int = 1;
		dbg_assert(iset_contains(set, &temp_int) == true);
		temp_int = 0;
		dbg_assert(iset_contains(set, &temp_int) == false);
	}

	/* test clear */
	{
		int temp_int;
		iset_clear(set);
		/* now the set is empty */
		dbg_assert(iset_empty(set));
		
		/* clear an empty set */
		iset_clear(set);
		dbg_assert(iset_empty(set));

		temp_int = 1;
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 1);
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 1);
		iset_insert(set, &temp_int);
		dbg_assert(temp_int == 1);

		/* now the set is { 1 } */
		iset_clear(set);
		dbg_assert(iset_empty(set));
	}
}

static int __num_modify; /* number of insert and remove */
static int __num_search;

static int __data_diff_type; /* number of different values to store in the set */
static int __data_max_count; /* max count of a single value */

static object __set = NULL; /* to be tested */
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

static void set_bench_modify_randomly() {
	int i;

	log_printline("[number of modify: %d]", __num_modify);
	dbg_assert(iset_empty(__set));

	for (i = 0; i < __num_modify; i ++) {
		intptr_t x = rand() % __data_diff_type;
		bool found = iset_contains(__set, (void*)x);
		
		if (found == false) {
			iset_insert(__set, &x);
			data_count[x] ++;
		} else {
			iset_remove(__set, &x);
			data_count[x] --;
		}
	}

	iset_clear(__set);
}

static void set_bench_search_randomly() {
	int i;
	dbg_assert(iset_empty(__set));

	log_printline("[number of search: %d]", __num_search);

	for (i = 0; i < __data_diff_type; i ++) {
		/* insert all data one by one */
		iset_insert(__set, &i);
	}
	/* now the set contains __data_diff_type * 2 of data, each elememt int [0, __data_diff_type)
	 * appears at least once */

	for (i = 0; i < __num_search; i ++) {
		intptr_t x = rand() % __data_diff_type;

		bool res = iset_contains(__set, (void*)x);
		dbg_assert(res == true);
	}

	iset_clear(__set);
}


void set_test_basic(object set) {
	set_test_basic_operation(set);
	set_test_basic_itr_operation(set);
}

void set_test_memory(object set) {
}

void set_test_bench(object set) {
	__set = set;
	__data_diff_type = 100;
	__data_max_count = 1;
	__num_modify     = 100;
	__num_search     = 100;
	iset_clear(__set);
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	
	__create_data();
	test_run_single("randomly modify test", set_bench_modify_randomly);
	__destroy_data();
	test_run_single("randomly search test", set_bench_search_randomly);

	__num_modify     = 100000;
	__num_search     = 100;
	__create_data();
	test_run_single("randomly modify test", set_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 100000;
	test_run_single("randomly search test", set_bench_search_randomly);

	__data_diff_type = 5000;
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	__num_modify     = 100000;
	__num_search     = 100;
	__create_data();
	test_run_single("randomly modify test", set_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 100000;
	test_run_single("randomly search test", set_bench_search_randomly);

	__data_diff_type = 100000;
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	__num_modify     = 100000;
	__num_search     = 100;

	__create_data();
	test_run_single("randomly modify test", set_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 100000;
	test_run_single("randomly search test", set_bench_search_randomly);

	__data_diff_type = 100000;
	log_printline("[data type: %d, single data max dup: %d]", __data_diff_type, __data_max_count);
	__num_modify     = 10000000;
	__num_search     = 100;

	__create_data();
	test_run_single("randomly modify test", set_bench_modify_randomly);
	__destroy_data();

	__num_modify     = 100;
	__num_search     = 10000000;
	test_run_single("randomly search test", set_bench_search_randomly);
}
