#include "cntr2/iarray.h"
#include "cntr2/iitr.h"
#include "cntr2/ifactory.h"

#include "iarray.test.h"
#include "test_util.h"
#include "ele.data.h"
#include "memheap/heap_global.h"

static void array_test_basic_itr_operation(Object* a, address td_repo[], unknown_traits *td_traits) {
	iarray_clear(a);
	dbg_assert(iarray_empty(a));

	iarray_add_front(a, td_repo[4]);
	iarray_add_back (a, td_repo[5]);
	iarray_add_front(a, td_repo[3]);
	iarray_add_back (a, td_repo[6]);
	iarray_add_front(a, td_repo[2]);
	iarray_add_back (a, td_repo[7]);
	iarray_add_front(a, td_repo[1]);
	iarray_add_back (a, td_repo[8]);
	/* now the a contains { 1, 2, 3, 4, 5, 6, 7, 8 } */

	/* check is repo is destroyed */
	dbg_assert(iarray_size(a) == 8);
	{
		iterator itr = iarray_itr_create(a, itr_begin);
		const_iterator end = iarray_itr_end(a);
		intptr_t current = 1;
		const unknown* x = NULL;

		/* traverse the a */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			x = itr_get_ref(itr);
			/* instance is managed by the container */
			dbg_assert(x != td_repo[current]);
			dbg_assert(td_traits->__equals(x, td_repo[current]));
			current ++;
		}

		/* test itr_assign */
		iarray_itr_assign(a, itr, itr_begin);
		x = itr_get_ref(itr);
		dbg_assert(td_traits->__equals(x, td_repo[1]));
		iarray_itr_assign(a, itr, itr_end);
		itr_to_prev(itr);
		x = (int*)itr_get_ref(itr);
		dbg_assert(td_traits->__equals(x, td_repo[8]));

		/* test itr_find */
		iarray_itr_find(a, itr, td_repo[0]);
		dbg_assert(itr_equals(itr, iarray_itr_end(a)));
		iarray_itr_find(a, itr, td_repo[9]);
		dbg_assert(itr_equals(itr, iarray_itr_end(a)));

		for (current = 1; current <= 8; current ++) {
			iarray_itr_find(a, itr, td_repo[current]);
			dbg_assert(!itr_equals(itr, iarray_itr_end(a)));
		}

		/* test itr_remove */
		iarray_itr_find(a, itr, td_repo[4]);
		dbg_assert(!itr_equals(itr, iarray_itr_end(a)));

		iarray_itr_remove(a, itr);
		/* now the a is { 1, 2, 3,  , 5, 6, 7, 8 } */
		dbg_assert(iarray_size(a) == 7);
		for (current = 0; current <= 9; current ++) {
			iarray_itr_find(a, itr, td_repo[current]);
			if (current == 0 || current == 9 || current == 4) {
				dbg_assert(itr_equals(itr, iarray_itr_end(a)));
			}
			else {
				dbg_assert(!itr_equals(itr, iarray_itr_end(a)));
			}
		}

		/* test continuous itr_remove */
		iarray_itr_find(a, itr, td_repo[5]);
		dbg_assert(!itr_equals(itr, iarray_itr_end(a)));

		iarray_itr_remove(a, itr);
		/* now the a is { 1, 2, 3,  , 6, 7, 8 } */
		dbg_assert(iarray_size(a) == 6);
		for (current = 0; current <= 9; current ++) {
			iarray_itr_find(a, itr, td_repo[current]);
			if (current == 0 || current == 9 || current == 4 || current == 5) {
				dbg_assert(itr_equals(itr, iarray_itr_end(a)));
			}
			else {
				dbg_assert(!itr_equals(itr, iarray_itr_end(a)));
			}
		}

		/* test insert_before */
		iarray_itr_find(a, itr, td_repo[6]);
		dbg_assert(!itr_equals(itr, iarray_itr_end(a)));

		/* now the a is { 1, 2, 3,  6, 7, 8 } */
		for (current = 1, iarray_itr_assign(a, itr, itr_begin); 
				!itr_equals(itr, end); 
				current ++) {
			if (current != 4 && current != 5) {
				x = itr_get_ref(itr);
				dbg_assert(td_traits->__equals(x, td_repo[current]));
				itr_to_next(itr);
			}
		}

		iarray_itr_find(a, itr, td_repo[3]);
		dbg_assert(!itr_equals(itr, iarray_itr_end(a)));

		/* now the a is { 1, 2, 3,  6, 7, 8 } */
		iarray_itr_assign(a, itr, itr_begin);
		for (current = 1; current <= 8; current ++) {
			if (current == 4 || current == 5) 
				continue;
			x = itr_get_ref(itr);
			dbg_assert(td_traits->__equals(x, td_repo[current]));
			itr_to_next(itr);
		}

		itr_destroy(itr);
	}

	return;
}

static void array_test_basic_operation(Object* a, address td_repo[], unknown_traits *td_traits) {
	iarray_clear(a);
	dbg_assert(iarray_empty(a));

	iarray_add_front(a, td_repo[4]);
	iarray_add_back (a, td_repo[5]);
	iarray_add_front(a, td_repo[3]);
	iarray_add_back (a, td_repo[6]);
	iarray_add_front(a, td_repo[2]);
	iarray_add_back (a, td_repo[7]);
	iarray_add_front(a, td_repo[1]);
	iarray_add_back (a, td_repo[8]);
	/* now the a contains { 1, 2, 3, 4, 5, 6, 7, 8 } */

	/* check is repo is destroyed */
	dbg_assert(iarray_size(a) == 8);
	{
		intptr_t current = 1;

		dbg_assert(td_traits->__equals(iarray_front(a), td_repo[1]));
		dbg_assert(td_traits->__equals(iarray_back (a), td_repo[8]));

		for (; current <= 8; current ++) {
			dbg_assert(iarray_contains(a, td_repo[current]));
		}
		dbg_assert(iarray_contains(a, td_repo[0]) == false);
		dbg_assert(iarray_contains(a, td_repo[0]) == false);
	}

	/* test remove, delete the even ones */
	dbg_assert(iarray_size(a) == 8);
	{
		/* now the a contains { 1, 2, 3, 4, 5, 6, 7, 8 } */
		intptr_t x;
		bool res;

		for (x = 2; x <= 8; x +=2) {
			res = iarray_remove(a, td_repo[x]);
			dbg_assert(res == 1);
		}

		dbg_assert(iarray_size(a) == 4);
		for (x = 1; x <= 8; x ++) {
			bool exist = x % 2 ? true : false;
			dbg_assert(iarray_contains(a, td_repo[x]) == exist);
		}

		dbg_assert(iarray_contains(a, td_repo[0]) == false);
		dbg_assert(iarray_contains(a, td_repo[9]) == false);
	}

	/* test remove_front and remove_back */
	dbg_assert(iarray_size(a) == 4);
	{
		/* now the a is {1, 3, 5, 7} */

		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[1]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[7]));

		iarray_remove_front(a);
		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[3]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[7]));
		dbg_assert(iarray_size(a) == 3);
		dbg_assert(iarray_empty(a) == false);

		iarray_remove_back(a);
		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[3]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[5]));
		dbg_assert(iarray_size(a) == 2);
		dbg_assert(iarray_empty(a) == false);

		iarray_remove_front(a);
		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[5]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[5]));
		dbg_assert(iarray_size(a) == 1);
		dbg_assert(iarray_empty(a) == false);

		iarray_remove_back(a);
		dbg_assert(iarray_front(a) == NULL);
		dbg_assert(iarray_back (a) == NULL);
		dbg_assert(iarray_size(a) == 0);
		dbg_assert(iarray_empty(a));

		/* now the a is empty, trying to remove from an empty a */
		iarray_remove_front(a);
		dbg_assert(iarray_size(a) == 0);
		dbg_assert(iarray_empty(a) == true);
		dbg_assert(iarray_front(a) == NULL);
		dbg_assert(iarray_back (a) == NULL);

		iarray_remove_back(a);
		dbg_assert(iarray_size(a) == 0);
		dbg_assert(iarray_empty(a) == true);
		dbg_assert(iarray_front(a) == NULL);
		dbg_assert(iarray_back (a) == NULL);

		/* trying to add element into the a after removing from empty a */
		iarray_add_front(a, td_repo[2]);
		/* now the a is { 2 } */
		dbg_assert(iarray_size(a) == 1);
		dbg_assert(iarray_empty(a) == false);
		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[2]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[2]));

		iarray_add_back (a, td_repo[3]);
		/* now the a is { 2, 3 } */
		dbg_assert(iarray_size(a) == 2);
		dbg_assert(iarray_empty(a) == false);
		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[2]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[3]));

		iarray_add_front(a, td_repo[1]);
		/* now the a is { 1, 2, 3 } */
		dbg_assert(iarray_size(a) == 3);
		dbg_assert(iarray_empty(a) == false);
		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[1]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[3]));

		iarray_add_back (a, td_repo[4]);
		/* now the a is { 1, 2, 3, 4 } */
		dbg_assert(iarray_size(a) == 4);
		dbg_assert(iarray_empty(a) == false);
		dbg_assert(td_traits->__equals(iarray_front(a),td_repo[1]));
		dbg_assert(td_traits->__equals(iarray_back (a),td_repo[4]));

		iarray_clear(a);
	}

	/* test clear */
	{
		/* now the a is empty */
		dbg_assert(iarray_empty(a));

		dbg_assert(iarray_front(a) == NULL);
		dbg_assert(iarray_back (a) == NULL);
		
		/* clear an empty a */
		iarray_clear(a);
		dbg_assert(iarray_empty(a));

		iarray_add_back(a, td_repo[1]);
		iarray_add_back(a, td_repo[1]);
		iarray_add_back(a, td_repo[1]);

		/* now the a is { 1, 1, 1 } */
		iarray_clear(a);
		dbg_assert(iarray_empty(a));
	}
}

void array_test_basic() {
	Object* a = cntr_create_oarray(&int_traits);
	array_test_basic_operation(a, int_repo, &int_traits);
	array_test_basic_itr_operation(a, int_repo, &int_traits);
	iobject_destroy(a);

	a = cntr_create_oarray(&longint_traits);
	array_test_basic_operation(a, longint_repo, &longint_traits);
	array_test_basic_itr_operation(a, longint_repo, &longint_traits);
	iobject_destroy(a);

	a = cntr_create_oarray(&float_traits);
	array_test_basic_operation(a, float_repo, &float_traits);
	array_test_basic_itr_operation(a, float_repo, &float_traits);
	iobject_destroy(a);

	a = cntr_create_oarray(&double_traits);
	array_test_basic_operation(a, double_repo, &double_traits);
	array_test_basic_itr_operation(a, double_repo, &double_traits);
	iobject_destroy(a);

	a = cntr_create_oarray(&char_traits);
	array_test_basic_operation(a, char_repo, &char_traits);
	array_test_basic_itr_operation(a, char_repo, &char_traits);
	iobject_destroy(a);

	a = cntr_create_oarray(&string_traits);
	array_test_basic_operation(a, string_repo, &string_traits);
	array_test_basic_itr_operation(a, string_repo, &string_traits);
	iobject_destroy(a);
}

void array_test_memory(Object* a) {
}

void array_test_bench(Object* a) {
	/* should this exist, or it just compares with the raw array_link to show the overhead of 'virtual' functions */
}

