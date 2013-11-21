#include "cntr2/ilist.h"
#include "cntr2/iitr.h"

#include "ilist.test.h"
#include "test_util.h"
#include "memheap/heap_global.h"

static void list_test_basic_itr_operation(ilist list) {
	int temp_int = 0;
	ilist_clear(list);
	dbg_assert(ilist_empty(list));

	temp_int = 4;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 4);
	temp_int = 5;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 5);
	temp_int = 3;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 6;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 6);
	temp_int = 2;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 7;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 7);
	temp_int = 1;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 8;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 8);
	/* now the list contains { 1, 2, 3, 4, 5, 6, 7, 8 } */

	dbg_assert(ilist_size(list) == 8);
	{
		iterator itr = ilist_itr_create(list, itr_begin);
		const_iterator end = ilist_itr_end(list);
		intptr_t current = 1;
		int* x = NULL;

		/* traverse the list */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			x = (int*)itr_get_ref(itr);
			dbg_assert(*x == current);
			current ++;
		}

		/* test itr_assign */
		ilist_itr_assign(list, itr, itr_begin);
		x = (int*)itr_get_ref(itr);
		dbg_assert(*x == 1);
		ilist_itr_assign(list, itr, itr_end);
		itr_to_prev(itr);
		x = (int*)itr_get_ref(itr);
		dbg_assert(*x == 8);

		/* test itr_find */
		temp_int = 0;
		ilist_itr_find(list, itr, &temp_int);
		dbg_assert(itr_equals(itr, ilist_itr_end(list)));
		temp_int = 9;
		ilist_itr_find(list, itr, &temp_int);
		dbg_assert(itr_equals(itr, ilist_itr_end(list)));

		for (current = 1; current <= 8; current ++) {
			ilist_itr_find(list, itr, &current);
			dbg_assert(!itr_equals(itr, ilist_itr_end(list)));
		}

		/* test itr_remove */
		temp_int = 4;
		ilist_itr_find(list, itr, &temp_int);
		dbg_assert(!itr_equals(itr, ilist_itr_end(list)));

		ilist_itr_remove(list, itr);
		/* now the list is { 1, 2, 3,  , 5, 6, 7, 8 } */
		dbg_assert(ilist_size(list) == 7);
		for (current = 0; current <= 9; current ++) {
			ilist_itr_find(list, itr, &current);
			if (current == 0 || current == 9 || current == 4) {
				dbg_assert(itr_equals(itr, ilist_itr_end(list)));
			}
			else {
				dbg_assert(!itr_equals(itr, ilist_itr_end(list)));
			}
		}

		/* test continuous itr_remove */
		temp_int = 5;
		ilist_itr_find(list, itr, &temp_int);
		dbg_assert(!itr_equals(itr, ilist_itr_end(list)));

		ilist_itr_remove(list, itr);
		/* now the list is { 1, 2, 3,  , 6, 7, 8 } */
		dbg_assert(ilist_size(list) == 6);
		for (current = 0; current <= 9; current ++) {
			ilist_itr_find(list, itr, &current);
			if (current == 0 || current == 9 || current == 4 || current == 5) {
				dbg_assert(itr_equals(itr, ilist_itr_end(list)));
			}
			else {
				dbg_assert(!itr_equals(itr, ilist_itr_end(list)));
			}
		}

		/* test insert_before */
		temp_int = 6;
		ilist_itr_find(list, itr, &temp_int);
		dbg_assert(!itr_equals(itr, ilist_itr_end(list)));

		temp_int = 5;
		ilist_itr_insert_before(list, itr, &temp_int);
		/* now the list is { 1, 2, 3,  5, 6, 7, 8 } */
		for (current = 1, ilist_itr_assign(list, itr, itr_begin); 
				!itr_equals(itr, end); 
				current ++) {
			if (current != 4) {
				x = (int*)itr_get_ref(itr);
				dbg_assert(*x == current);
				itr_to_next(itr);
			}
		}

		/* test insert_after */
		temp_int = 3;
		ilist_itr_find(list, itr, &temp_int);
		dbg_assert(!itr_equals(itr, ilist_itr_end(list)));

		temp_int = 4;
		ilist_itr_insert_after(list, itr, &temp_int);
		/* now the list is { 1, 2, 3, 4, 5, 6, 7, 8 } */
		for (current = 1, ilist_itr_assign(list, itr, itr_begin); 
				!itr_equals(itr, end); 
				itr_to_next(itr), current ++) {
					x = (int*)itr_get_ref(itr);
					dbg_assert(*x == current);
		}

		itr_destroy(itr);
	}

	return;
}

static void list_test_basic_operation(ilist list) {
	int temp_int = 0;
	ilist_clear(list);
	dbg_assert(ilist_empty(list));

	temp_int = 4;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 4);
	temp_int = 5;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 5);
	temp_int = 3;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 6;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 6);
	temp_int = 2;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 7;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 7);
	temp_int = 1;
	ilist_add_front(list, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 8;
	ilist_add_back (list, &temp_int);
	dbg_assert(temp_int == 8);
	/* now the list contains { 1, 2, 3, 4, 5, 6, 7, 8 } */
	dbg_assert(ilist_size(list) == 8);
	{
		intptr_t current = 1;

		dbg_assert(*(int*)ilist_front(list) == 1);
		dbg_assert(*(int*)ilist_back (list) == 8);

		for (; current <= 8; current ++) {
			dbg_assert(ilist_contains(list, &current));
		}
		temp_int = 0;
		dbg_assert(ilist_contains(list, &temp_int) == false);
		temp_int = 0;
		dbg_assert(ilist_contains(list, &temp_int) == false);
	}

	/* test remove, delete the even ones */
	dbg_assert(ilist_size(list) == 8);
	{
		/* now the list contains { 1, 2, 3, 4, 5, 6, 7, 8 } */
		intptr_t x;
		bool res;

		for (x = 2; x <= 8; x +=2) {
			res = ilist_remove(list, &x);
			dbg_assert(res == 1);
		}

		dbg_assert(ilist_size(list) == 4);
		for (x = 1; x <= 8; x ++) {
			bool exist = x % 2 ? true : false;
			dbg_assert(ilist_contains(list, &x) == exist);
		}

		temp_int = 0;
		dbg_assert(ilist_contains(list, &temp_int) == false);
		temp_int = 9;
		dbg_assert(ilist_contains(list, &temp_int) == false);
	}

	/* test remove_front and remove_back */
	dbg_assert(ilist_size(list) == 4);
	{
		/* now the list is {1, 3, 5, 7} */

		dbg_assert(*(int*)ilist_front(list) == 1);
		dbg_assert(*(int*)ilist_back (list) == 7);

		ilist_remove_front(list);
		dbg_assert(*(int*)ilist_front(list) == 3);
		dbg_assert(*(int*)ilist_back (list) == 7);
		dbg_assert(ilist_size(list) == 3);
		dbg_assert(ilist_empty(list) == false);

		ilist_remove_back(list);
		dbg_assert(*(int*)ilist_front(list) == 3);
		dbg_assert(*(int*)ilist_back (list) == 5);
		dbg_assert(ilist_size(list) == 2);
		dbg_assert(ilist_empty(list) == false);

		ilist_remove_front(list);
		dbg_assert(*(int*)ilist_front(list) == 5);
		dbg_assert(*(int*)ilist_back (list) == 5);
		dbg_assert(ilist_size(list) == 1);
		dbg_assert(ilist_empty(list) == false);

		ilist_remove_back(list);
		dbg_assert(ilist_front(list) == NULL);
		dbg_assert(ilist_back (list) == NULL);
		dbg_assert(ilist_size(list) == 0);
		dbg_assert(ilist_empty(list));

		/* now the list is empty, trying to remove from an empty list */
		ilist_remove_front(list);
		dbg_assert(ilist_size(list) == 0);
		dbg_assert(ilist_empty(list) == true);
		dbg_assert(ilist_front(list) == NULL);
		dbg_assert(ilist_back (list) == NULL);

		ilist_remove_back(list);
		dbg_assert(ilist_size(list) == 0);
		dbg_assert(ilist_empty(list) == true);
		dbg_assert(ilist_front(list) == NULL);
		dbg_assert(ilist_back (list) == NULL);

		/* trying to add element into the list after removing from empty list */
		temp_int = 2;
		ilist_add_front(list, &temp_int);
		dbg_assert(temp_int == 2);
		/* now the list is { 2 } */
		dbg_assert(ilist_size(list) == 1);
		dbg_assert(ilist_empty(list) == false);
		dbg_assert(*(int*)ilist_front(list) == 2);
		dbg_assert(*(int*)ilist_back (list) == 2);

		temp_int = 3;
		ilist_add_back (list, &temp_int);
		dbg_assert(temp_int == 3);
		/* now the list is { 2, 3 } */
		dbg_assert(ilist_size(list) == 2);
		dbg_assert(ilist_empty(list) == false);
		dbg_assert(*(int*)ilist_front(list) == 2);
		dbg_assert(*(int*)ilist_back (list) == 3);

		temp_int = 1;
		ilist_add_front(list, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the list is { 1, 2, 3 } */
		dbg_assert(ilist_size(list) == 3);
		dbg_assert(ilist_empty(list) == false);
		dbg_assert(*(int*)ilist_front(list) == 1);
		dbg_assert(*(int*)ilist_back (list) == 3);

		temp_int = 4;
		ilist_add_back (list, &temp_int);
		dbg_assert(temp_int == 4);
		/* now the list is { 1, 2, 3, 4 } */
		dbg_assert(ilist_size(list) == 4);
		dbg_assert(ilist_empty(list) == false);
		dbg_assert(*(int*)ilist_front(list) == 1);
		dbg_assert(*(int*)ilist_back (list) == 4);

		ilist_clear(list);
	}

	/* test clear */
	{
		/* now the list is empty */
		dbg_assert(ilist_empty(list));

		dbg_assert(ilist_front(list) == NULL);
		dbg_assert(ilist_back (list) == NULL);
		
		/* clear an empty list */
		ilist_clear(list);
		dbg_assert(ilist_empty(list));

		temp_int = 1;
		ilist_add_back(list, &temp_int);
		dbg_assert(temp_int == 1);
		ilist_add_back(list, &temp_int);
		dbg_assert(temp_int == 1);
		ilist_add_back(list, &temp_int);
		dbg_assert(temp_int == 1);

		/* now the list is { 1, 1, 1 } */
		ilist_clear(list);
		dbg_assert(ilist_empty(list));
	}
}

void list_test_basic(ilist list) {

	list_test_basic_operation(list);

	list_test_basic_itr_operation(list);
}

void list_test_memory(ilist list) {
}

void list_test_bench(ilist list) {
	/* should this exist, or it just compares with the raw list_link to show the overhead of 'virtual' functions */
}

