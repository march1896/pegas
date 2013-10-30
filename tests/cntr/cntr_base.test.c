#include <cntr.h>

#include <cntr/cntr_test_util.h>

#include <stdio.h>
#include <string.h>

static void add_find_remove_correctness_test(TC_TYPE ct, TD_TYPE dt, TD_LENGTH dl) {
	cntr c;
	citer_dos(first, NULL);
	citer_dos(second, NULL);
	int i, length, ulength;

	if (dt == TD_UNIQUE) {
		if (ct >= TC_BST && ct <= TC_234T) 
			return;
	}

	printf("%s add/find/remove test with %s data\n", cntr_name(ct), data_order_name(dt));

	c = cntr_create(ct);

	generate_test_data(dt, dl, &length, &ulength);

	for (i = 0; i < ulength; i ++) cntr_add(c, (void*)(intptr_t)uniquedata[i]);

	/* test find */
	for (i = 0; i < length; i ++) {
		bool find = cntr_find(c, (void*)(intptr_t)rawdata[i], first);
		dbg_assert(find);
	}

	for (i = length + 1; i < length + 50; i ++) {
		bool find = cntr_find(c, (void*)(intptr_t)i, first);
		dbg_assert(find == false);
	}

	/* test remove, remove first half elements */
	for (i = 0; i < ulength; i ++) {
		bool find = cntr_find(c, (void*)(intptr_t)uniquedata[i], first);
		cntr_remove(c, first, first);
		dbg_assert(cntr_size(c) == ulength - i - 1);
	}

	cntr_clear(c);
	dbg_assert(cntr_size(c) == 0);

	cntr_destroy(c);
}

static void add_find_remove_performance_test(TC_TYPE ct, TD_TYPE dt, TD_LENGTH dl) {
	cntr c;
	citer_dos(first, NULL);
	citer_dos(second, NULL);
	int rep, i, length, ulength;
	clock_t start_c, end_c;
	float find_used;

	if (dt == TD_UNIQUE) {
		if (ct >= TC_BST && ct <= TC_234T) 
			return;
	}

	printf("\n%s add/find/remove performance test with %s data\n", cntr_name(ct), data_order_name(dt));

	c = cntr_create(ct);

	generate_test_data(dt, dl, &length, &ulength);

	printf("add: ");
	start_c = clock();	
	for (i = 0; i < length; i ++) {
		cntr_add(c, (void*)(intptr_t)rawdata[i]);
	}
	end_c = clock();
	printf("used %f\n", (float)(end_c - start_c)/CLOCKS_PER_SEC);

	printf("find: ");
	start_c = clock();
	for (rep = 0; rep < 20; rep ++) {
		for (i = 0; i < length; i ++) {
			bool find = cntr_find(c, (void*)(intptr_t)rawdata[i], first);
			dbg_assert(find);
		}
	}
	end_c = clock();
	printf("used %f\n", (float)(end_c - start_c)/CLOCKS_PER_SEC);
	find_used = (float)(end_c - start_c)/CLOCKS_PER_SEC;


	printf("remove: ");
	find_used = 0.0;
	start_c = clock();
	for (i = 0; i < ulength; i ++) {
		bool find = cntr_find(c, (void*)(intptr_t)uniquedata[i], first);

		cntr_remove(c, first, first);
	}
	end_c = clock();
	printf("used %f\n", (float)(end_c - start_c)/CLOCKS_PER_SEC - find_used);

	cntr_clear(c);
	dbg_assert(cntr_size(c) == 0);

	cntr_destroy(c);
}

static void cntr_base_memory_test() {
	
}

static void cntr_base_correctness_test() {
	int i, j;
	printf("add find remove correctness test start\n");
	for (i = TC_LIST; i < TC_END; i ++) {
		for (j = TD_INCREASE; j < TD_END; j ++) {
			add_find_remove_correctness_test((TC_TYPE)i, (TD_TYPE)j, TL_CORRECTNESS);
		}
	}
	printf("add find remove correctness test end\n");
}

static void cntr_base_performance_test() {
	int i, j;
	printf("add find remove performance test start\n");
	for (i = TC_RBT; i < TC_END; i ++) {
		for (j = TD_INCREASE; j < TD_END; j ++) {
			add_find_remove_performance_test((TC_TYPE)i, (TD_TYPE)j, TL_PERFORMANCE);
		}
	}
	printf("add find remove performance test end\n");
}

void cntr_base_test() {
	do_test("cntr cntr_base correctness", cntr_base_correctness_test);

	do_test("cntr cntr_base performance", cntr_base_performance_test);
}
