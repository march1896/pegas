#include "cntr2/istack.h"
#include "cntr2/iitr.h"

#include "istack.test.h"
#include "test_util.h"

#include "memheap/heap_global.h"

static void stack_test_basic_itr_operation(istack stack) {
	int temp_int = 0;
	istack_clear(stack);
	dbg_assert(istack_size(stack) == 0);

	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 2;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 3;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 4;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 4);

	/* now the stack contains { 1, 2, 3, 4 } */
	dbg_assert(istack_size(stack) == 4);
	{
		iterator itr = istack_itr_create(stack, itr_begin);
		const_iterator end = istack_itr_end(stack);
		intptr_t current = 1;
		int* x = NULL;

		/* traverse the stack */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			x = (int*)itr_get_ref(itr);
			dbg_assert(*x == current);
			current ++;
		}

		/* test itr_assign */
		istack_itr_assign(stack, itr, itr_begin);
		x = (int*)itr_get_ref(itr);
		dbg_assert(*x == 1);
		istack_itr_assign(stack, itr, itr_end);
		itr_to_prev(itr);
		x = (int*)itr_get_ref(itr);
		dbg_assert(*x == 4);

		itr_destroy(itr);
	}

	istack_clear(stack);
	dbg_assert(istack_size(stack) == 0);

	/* test unique data */
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);

	/* now the stack contains eight 1s, { 1, 1, 1, 1, 1, 1, 1, 1 } */
	dbg_assert(istack_size(stack) == 8);
	{
		iterator itr = istack_itr_create(stack, itr_begin);
		const_iterator end = istack_itr_end(stack);

		/* traverse the stack */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			int* x = (int*)itr_get_ref(itr);
			dbg_assert(*x == 1);
		}

		itr_destroy(itr);
	}

	return;
}

static void stack_test_basic_operation(istack stack) {
	int temp_int;
	istack_clear(stack);
	dbg_assert(istack_size(stack) == 0);
	dbg_assert(istack_empty(stack));

	temp_int = 1;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 2;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 3;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 4;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 4);
	temp_int = 5;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 5);
	temp_int = 6;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 6);
	temp_int = 7;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 7);
	temp_int = 8;
	istack_push(stack, &temp_int);
	dbg_assert(temp_int == 8);
	/* now the stack contains { 1, 2, 3, 4, 5, 6, 7, 8 } */

	/* test pop */
	dbg_assert(istack_size(stack) == 8);
	{
		/* now the stack contains { 1, 2, 3, 4, 5, 6, 7, 8 } */
		intptr_t counter = 1;

		dbg_assert(*(int*)istack_top  (stack) == 8);

		for (counter = 8; counter >= 1; counter --) {
			istack_pop(stack);
		}
	}

	/* test intersect push and pop */
	{
		intptr_t element = 0;

		dbg_assert(istack_empty(stack));
		temp_int = 1;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 2;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 2);
		/* push two element, now is { 1, 2 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 2);
		dbg_assert(*(int*)istack_top  (stack) == 2);

		istack_pop(stack);
		/* remove the top one, now is { 1 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 1);
		dbg_assert(*(int*)istack_top  (stack) == 1);

		temp_int = 3;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 3);
		temp_int = 4;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 4);
		/* push another 2 element, now is { 1, 3, 4 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 3);
		dbg_assert(*(int*)istack_top  (stack) == 4);

		/* continuous pop all of them */
		istack_pop(stack);
		/* remove the top one, now is { 1, 3 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 2);
		dbg_assert(*(int*)istack_top  (stack) == 3);

		istack_pop(stack);
		/* remove the top one, now is { 1 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 1);
		dbg_assert(*(int*)istack_top  (stack) == 1);

		istack_pop(stack);
		/* remove the top one, now is {} */
		dbg_assert(istack_empty(stack) == true);
		dbg_assert(istack_size (stack) == 0);
		dbg_assert(istack_top  (stack) == NULL);

		/* trying to pop empty stack */
		istack_pop(stack);
		dbg_assert(istack_empty(stack) == true);
		dbg_assert(istack_size (stack) == 0);
		dbg_assert(istack_top  (stack) == NULL);

		/* trying to push an element after pop empty stack */
		temp_int = 1;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 1);
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 1);
		dbg_assert(*(int*)istack_top  (stack) == 1);
	}

	/* test unique element */
	{
		istack_clear(stack);

		temp_int = 1;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 1;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 1;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the stack is { 1, 1, 1 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 3);
		dbg_assert(*(int*)istack_top  (stack) == 1);

		istack_pop(stack);
		/* remove the top one, now is { 1, 1 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 2);
		dbg_assert(*(int*)istack_top  (stack) == 1);

		temp_int = 1;
		istack_push(stack, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the stack is { 1, 1, 1 } */
		dbg_assert(istack_empty(stack) == false);
		dbg_assert(istack_size (stack) == 3);
		dbg_assert(*(int*)istack_top  (stack) == 1);

		istack_clear(stack);
	}
}

void stack_test_basic(istack stack) {

	stack_test_basic_operation(stack);

	stack_test_basic_itr_operation(stack);
}

void stack_test_memory(istack stack) {
}

void stack_test_bench(istack stack) {
	/* should this exist, or it just compares with the raw stack_link to show the overhead of 'virtual' funtions */
}

