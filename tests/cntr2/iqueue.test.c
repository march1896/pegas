#include "cntr2/iqueue.h"
#include "cntr2/iitr.h"

#include "iqueue.test.h"
#include "test_util.h"

#include "memheap/heap_global.h"

static void queue_test_basic_itr_operation(iqueue queue) {
	int temp_int = 0;
	iqueue_clear(queue);
	dbg_assert(iqueue_size(queue) == 0);

	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 2;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 3;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 4;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 4);

	/* now the queue contains { 1, 2, 3, 4 } */
	dbg_assert(iqueue_size(queue) == 4);
	{
		iterator itr = iqueue_itr_create(queue, itr_begin);
		const_iterator end = iqueue_itr_end(queue);
		intptr_t current = 1;
		int* x = NULL;

		/* traverse the queue */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			x = (int*)itr_getvar(itr);
			dbg_assert(*x == current);
			hfree(x);
			current ++;
		}

		/* test itr_assign */
		iqueue_itr_assign(queue, itr, itr_begin);
		x = (int*)itr_getvar(itr);
		dbg_assert(*x == 1);
		hfree(x);
		iqueue_itr_assign(queue, itr, itr_end);
		itr_to_prev(itr);
		x = (int*)itr_getvar(itr);
		dbg_assert(*x == 4);
		hfree(x);

		itr_destroy(itr);
	}

	iqueue_clear(queue);
	dbg_assert(iqueue_size(queue) == 0);

	/* test unique data */
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);

	/* now the queue contains eight 1s, { 1, 1, 1, 1, 1, 1, 1, 1 } */
	dbg_assert(iqueue_size(queue) == 8);
	{
		iterator itr = iqueue_itr_create(queue, itr_begin);
		const_iterator end = iqueue_itr_end(queue);

		/* traverse the queue */
		for (; !itr_equals(itr, end); itr_to_next(itr)) {
			int* x = (int*)itr_getvar(itr);
			dbg_assert(*x == 1);
			hfree(x);
		}

		itr_destroy(itr);
	}

	return;
}

static void queue_test_basic_operation(iqueue queue) {
	int temp_int = 0;
	iqueue_clear(queue);
	dbg_assert(iqueue_size(queue) == 0);
	dbg_assert(iqueue_empty(queue));

	temp_int = 1;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 1);
	temp_int = 2;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 2);
	temp_int = 3;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 3);
	temp_int = 4;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 4);
	temp_int = 5;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 5);
	temp_int = 6;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 6);
	temp_int = 7;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 7);
	temp_int = 8;
	iqueue_push(queue, &temp_int);
	dbg_assert(temp_int == 8);
	/* now the queue contains { 1, 2, 3, 4, 5, 6, 7, 8 } */

	/* test pop */
	dbg_assert(iqueue_size(queue) == 8);
	{
		/* now the queue contains { 1, 2, 3, 4, 5, 6, 7, 8 } */
		intptr_t counter = 1;

		dbg_assert(*(int*)iqueue_front(queue) == 1);
		dbg_assert(*(int*)iqueue_back (queue) == 8);

		for (counter = 1; counter <= 8; counter ++) {
			iqueue_pop(queue);
		}
	}

	/* test intersect push and pop */
	{
		intptr_t element = 0;

		dbg_assert(iqueue_empty(queue));
		temp_int = 1;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 2;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 2);
		/* push two element, now is { 1, 2 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 2);
		dbg_assert(*(int*)iqueue_front(queue) == 1);
		dbg_assert(*(int*)iqueue_back (queue) == 2);

		iqueue_pop(queue);
		/* remove the front one, now is { 2 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 1);
		dbg_assert(*(int*)iqueue_front(queue) == 2);
		dbg_assert(*(int*)iqueue_back (queue) == 2);

		temp_int = 3;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 3);
		temp_int = 4;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 4);
		/* push another 2 element, now is { 2, 3, 4 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 3);
		dbg_assert(*(int*)iqueue_front(queue) == 2);
		dbg_assert(*(int*)iqueue_back (queue) == 4);

		/* continuous pop all of them */
		iqueue_pop(queue);
		/* remove the front one, now is { 3, 4 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 2);
		dbg_assert(*(int*)iqueue_front(queue) == 3);
		dbg_assert(*(int*)iqueue_back (queue) == 4);

		iqueue_pop(queue);
		/* remove the front one, now is { 4 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 1);
		dbg_assert(*(int*)iqueue_front(queue) == 4);
		dbg_assert(*(int*)iqueue_back (queue) == 4);

		iqueue_pop(queue);
		/* remove the front one, now is {} */
		dbg_assert(iqueue_empty(queue) == true);
		dbg_assert(iqueue_size (queue) == 0);
		dbg_assert(iqueue_front(queue) == NULL);
		dbg_assert(iqueue_back (queue) == NULL);

		/* trying to pop empty queue */
		iqueue_pop(queue);
		dbg_assert(iqueue_empty(queue) == true);
		dbg_assert(iqueue_size (queue) == 0);
		dbg_assert(iqueue_front(queue) == NULL);
		dbg_assert(iqueue_back (queue) == NULL);

		/* trying to push an element after pop empty queue */
		temp_int = 1;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 1);
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 1);
		dbg_assert(*(int*)iqueue_front(queue) == 1);
		dbg_assert(*(int*)iqueue_back (queue) == 1);
	}

	/* test unique element */
	{
		intptr_t element = 0;
		iqueue_clear(queue);

		temp_int = 1;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 1;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 1);
		temp_int = 1;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the queue is { 1, 1, 1 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 3);
		dbg_assert(*(int*)iqueue_front(queue) == 1);
		dbg_assert(*(int*)iqueue_back (queue) == 1);

		iqueue_pop(queue);
		/* remove the front one, now is { 1, 1 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 2);
		dbg_assert(*(int*)iqueue_front(queue) == 1);
		dbg_assert(*(int*)iqueue_back (queue) == 1);

		temp_int = 1;
		iqueue_push(queue, &temp_int);
		dbg_assert(temp_int == 1);
		/* now the queue is { 1, 1, 1 } */
		dbg_assert(iqueue_empty(queue) == false);
		dbg_assert(iqueue_size (queue) == 3);
		dbg_assert(*(int*)iqueue_front(queue) == 1);
		dbg_assert(*(int*)iqueue_back (queue) == 1);

		iqueue_clear(queue);
	}
}

void queue_test_basic(iqueue queue) {

	queue_test_basic_operation(queue);

	queue_test_basic_itr_operation(queue);
}

void queue_test_memory(iqueue queue) {
}

void queue_test_bench(iqueue queue) {
	/* should this exist, or it just compares with the raw queue_link to show the overhead of 'virtual' funtions */
}

