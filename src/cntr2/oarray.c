#include <string.h>

#include "iobject.h"
#include "iarray.h"
#include "iqueue.h"
#include "istack.h"
#include "iitr.h"
#include "ifactory.h"

#include "oarray.h"
#include "oallocator.h"

enum list_interfaces {
	e_object,
	e_array,
	e_queue,
	e_stack,
	e_l_count
};

struct oarray;
struct oarray_itr {
	address                       __offset;
	pf_cast                       __cast;

	/* there is always one interface to implement, since the interface is inherited */
	struct base_interface         __iftable[itr_interface_count];

	struct oarray*                container;
	/* the iterator will never alloc memory, when acquire an iterator, the container will 
	 * alloc the memory, but we should know how to delete this memory */
	allocator                     allocator;

	unknown*                      current;
};

struct oarray {
	address                       __offset;
	pf_cast                       __cast;
	
	struct base_interface         __iftable[e_l_count];

	int                           size;
	unknown_traits                content_traits;

	void*                         buffer;
	int                           buffer_length;
	int                           idx_start;
	int                           idx_end;
	int                           threshhold; /* minimum buffer length */

	/* methods to manage the inner memory use by the container */
	allocator                     allocator;
	bool                          allocator_join_ondispose;

	struct oarray_itr             itr_begin;
	struct oarray_itr             itr_end;
};

static struct iobject_vtable __array_iobject_vtable = {
	oarray_destroy,          /* __destroy */
	oarray_clone,            /* __clone */
	oarray_equals,           /* __equals */
	oarray_compare_to,       /* __compare_to */
	oarray_hashcode,         /* __hashcode */
};

static struct iarray_vtable __array_iarray_vtable = {
	oarray_clear,            /* __clear */
	oarray_foreach,          /* __foreach */
	oarray_size,             /* __size */
	oarray_empty,            /* __empty */
	oarray_front,            /* __front */
	oarray_back,             /* __back */
	oarray_at,               /* __at */
	oarray_add_front,        /* __add_front */
	oarray_add_back,         /* __add_back */
	oarray_remove_front,     /* __remove_front */
	oarray_remove_back,      /* __remove_back */
	oarray_contains,         /* __contains */
	oarray_remove,           /* __remove  */

	oarray_itr_begin,        /* __itr_begin */
	oarray_itr_end,          /* __itr_end */
	oarray_itr_create,       /* __itr_create */
	oarray_itr_assign,       /* __itr_assign */
	oarray_itr_find,         /* __itr_find */
	oarray_itr_remove,       /* __itr_remove */
};

static struct iqueue_vtable __array_iqueue_vtable = {
	oarray_clear,            /* __clear */
	oarray_foreach,          /* __foreach */
	oarray_size,             /* __size */
	oarray_empty,            /* __empty */
	oarray_front,            /* __front */
	oarray_back,             /* __back */
	oarray_add_back,         /* __push */
	oarray_remove_front,     /* __pop */
	oarray_itr_create,       /* __itr_create */
	oarray_itr_assign,       /* __itr_assign */
	oarray_itr_begin,        /* __itr_begin */
	oarray_itr_end           /* __itr_end */
};

static struct istack_vtable __array_istack_vtable = {
	oarray_clear,            /* __clear */
	oarray_foreach,          /* __foreach */
	oarray_size,             /* __size */
	oarray_empty,            /* __empty */
	oarray_back,             /* __top */
	oarray_add_back,         /* __push */
	oarray_remove_back,      /* __pop */
	oarray_itr_create,       /* __itr_create */
	oarray_itr_assign,       /* __itr_assign */
	oarray_itr_begin,        /* __itr_begin */
	oarray_itr_end           /* __itr_end */
};

static unknown* oarray_itr_cast(unknown* x, unique_id inf_id);
static unknown* oarray_cast(unknown* x, unique_id intf_id);

static void oarray_itr_destroy(iterator citr);
static iterator oarray_itr_clone(const_iterator citr);
static bool oarray_itr_equals(const_iterator a, const_iterator b);
static int oarray_itr_compare_to(const_iterator itr, const_iterator other);
static hashcode oarray_itr_hashcode(const_iterator itr);
static unknown* oarray_itr_get_obj(const_iterator citr);
static void oarray_itr_set_obj(iterator citr, const unknown* n_ref);
static const unknown* oarray_itr_get_ref(const_iterator citr);
static void oarray_itr_swap_ref(iterator citr, iterator other);
static void oarray_itr_to_next(iterator citr);
static void oarray_itr_to_prev(iterator citr);

static void oarray_itr_destroy(iterator citr) {
	struct oarray_itr* itr = (struct oarray_itr*)citr;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == oarray_itr_cast);

	/* destroy itself */
	allocator_dealloc(itr->allocator, itr);
}

static iterator oarray_itr_clone(const_iterator citr) {
	struct oarray_itr* itr = (struct oarray_itr*)citr;
	struct oarray_itr* n_itr = NULL;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == oarray_itr_cast);

	n_itr = (struct oarray_itr*)allocator_alloc(itr->allocator, sizeof(struct oarray_itr));

	memcpy(n_itr, itr, sizeof(struct oarray_itr));
	/* this is error prone */
	n_itr->__offset = n_itr;

	return (iterator)n_itr;
}

static bool oarray_itr_equals(const_iterator a, const_iterator b) {
	const struct oarray_itr* itr_a = (const struct oarray_itr*)a;
	const struct oarray_itr* itr_b = (const struct oarray_itr*)b;

	dbg_assert(__is_object((unknown*)a));
	dbg_assert(__is_object((unknown*)b));
	dbg_assert(itr_a->__cast == oarray_itr_cast);
	dbg_assert(itr_b->__cast == oarray_itr_cast);

	return itr_a->current == itr_b->current;
}

static int oarray_itr_compare_to(const_iterator itr, const_iterator other) {
	// TODO
	dbg_assert(false);
	return 0;
}
static hashcode oarray_itr_hashcode(const_iterator itr) {
	// TODO
	dbg_assert(false);
	return 0;
}

static unknown* oarray_itr_get_obj(const_iterator citr) {
// 	const struct oarray_itr* itr   = (const struct oarray_itr*)citr;
// 	const struct oarray_node* node = NULL;
// 	struct oarray* container = itr->container;
// 
// 	dbg_assert(itr->__cast == oarray_itr_cast);
// 	dbg_assert(itr->current != NULL);
// 
// 	node = container_of(itr->current, struct oarray_node, link);
// 
// 	/* return a internal reference as the iitr.h header said */
// 	return container->content_traits.__clone(node->reference, (pf_alloc)__global_default_alloc, __global_default_heap);
}

static void oarray_itr_set_obj(iterator citr, const unknown* n_ref) {
// 	struct oarray_itr* itr   = (struct oarray_itr*)citr;
// 	struct oarray_node* node = NULL;
// 	struct oarray* container = itr->container;
// 
// 	dbg_assert(itr->__cast == oarray_itr_cast);
// 	dbg_assert(itr->current != NULL);
// 
// 	node = container_of(itr->current, struct oarray_node, link);
// 	
// 	/* first destroy the old reference */
// 	container->content_traits.__destroy(node->reference, (pf_dealloc)allocator_release, container->allocator);
// 
// 	/* then clone the new reference */
// 	node->reference = 
// 		container->content_traits.__clone(n_ref, (pf_alloc)allocator_acquire, container->allocator);
}

static const unknown* oarray_itr_get_ref(const_iterator citr) {

}

static void oarray_itr_swap_ref(iterator citr, iterator other) {

}

static void oarray_itr_to_next(iterator citr) {
	struct oarray_itr* itr = (struct oarray_itr*)citr;

	dbg_assert(itr->__cast == oarray_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = itr->current->next;
}

static void oarray_itr_to_prev(iterator citr) {
	struct oarray_itr* itr = (struct oarray_itr*)citr;

	dbg_assert(itr->__cast == oarray_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = itr->current->prev;
}

static struct iobject_vtable __array_itr_iobject_vtable = {
	oarray_itr_destroy,      /* __destroy */
	oarray_itr_clone,        /* __clone   */
	oarray_itr_equals,       /* __equals  */
	oarray_itr_compare_to,   /* __compare_to */
	oarray_itr_hashcode
};

static struct itr_randomaccessible_vtable __array_itr_vtable = {
	oarray_itr_get_obj,      /* __get_obj */
	oarray_itr_get_ref,      /* __get_ref */
	oarray_itr_set_obj,      /* __set_obj */
	oarray_itr_swap_ref,     /* __swap_ref */
	oarray_itr_to_next,      /* __to_next */
	oarray_itr_to_prev       /* __to_prev */
};

static unknown* oarray_cast(unknown* x, unique_id intf_id) {
	struct oarray* o = (struct oarray*)x;

	dbg_assert(__is_object(x));

	switch (intf_id) {
	case IOBJECT_ID:
		return (unknown*)&o->__iftable[e_object];
	case ILIST_ID:
		return (unknown*)&o->__iftable[e_array];
	case IQUEUE_ID:
		return (unknown*)&o->__iftable[e_queue];
	case ISTACK_ID:
		return (unknown*)&o->__iftable[e_stack];
	default:
		return NULL;
	}

	return NULL;
}

static unknown* oarray_itr_cast(unknown* x, unique_id inf_id) {
	struct oarray_itr* itr = (struct oarray_itr*)x;

	dbg_assert(__is_object(itr));

	switch (inf_id) {
	case IOBJECT_ID:
		return (unknown*)&itr->__iftable[itr_interface_iobject];
	case ITR_REF_ID:
	case ITR_ACC_ID:
	case ITR_FWD_ID:
	case ITR_BID_ID:
	case ITR_RAC_ID:
		return (unknown*)&itr->__iftable[itr_interface_iterator];
	default:
		return NULL;
	}

	return NULL;
}

Object* cntr_create_array(unknown_traits content_traits) {
	return oarray_create(content_traits, __global_default_allocator);
}
Object* cntr_create_array_a(unknown_traits content_traits, allocator alc) {
	return oarray_create(content_traits, alc);
}

static void oarray_adjust_buffer(struct oarray *array);
static void oarray_itr_com_init(struct oarray_itr* itr, struct oarray* list);
Object* oarray_create(unknown_traits content_traits, allocator alc) {
	struct oarray* array = NULL;
	bool managed_allocator = false;

	if (alc == NULL) {
		alc = allocator_mpool_spawn(__global_default_allocator, 10);
		managed_allocator = true;
	}

	array = (struct oarray*)allocator_alloc(alc, sizeof(struct oarray));

	array->__offset = array;
	array->__cast   = oarray_cast;
	
	array->__iftable[e_object].__offset = (address)e_object;
	array->__iftable[e_object].__vtable = &__array_iobject_vtable;
	array->__iftable[e_array].__offset  = (address)e_array;
	array->__iftable[e_array].__vtable  = &__array_ilist_vtable;
	array->__iftable[e_queue].__offset  = (address)e_queue;
	array->__iftable[e_queue].__vtable  = &__array_iqueue_vtable;
	array->__iftable[e_stack].__offset  = (address)e_stack;
	array->__iftable[e_stack].__vtable  = &__array_istack_vtable;

	array->size = 0;
	array->content_traits = content_traits;
	array->buffer = NULL;
	array->buffer_length = 0;
	array->idx_start = 0;
	array->idx_end = 0;
	array->threshhold = 16;

	oarray_adjust_buffer(array);

	array->allocator = alc;
	array->allocator_join_ondispose = managed_allocator;

	oarray_itr_com_init(&array->itr_begin, array);
	oarray_itr_com_init(&array->itr_end, array);

	return (Object*)array;
}

static void oarray_adjust_buffer(struct oarray *array) {
	int n_length = -1;
	void* n_buffer = NULL;
	int threshhold = array->threshhold;

	if (array->buffer == NULL) {
		/* initialization */
		array->buffer = allocator_alloc(array->allocator, threshhold);
		array->buffer_length = threshhold;
		array->idx_start = 0;
		array->idx_end = 0;
		return;
	}

	if (array->idx_start <= array->idx_end) {
		dbg_assert(array->size == array->idx_end - array->idx_start);
	} else {
		dbg_assert(array->size == array->buffer_length - (array->idx_start - array->idx_end));
	}

	if (array->size == array->buffer_length) {
		/* expand the buffer to doulbe size */
		n_length = 2 * array->size;
	} else if (array->size < array->buffer_length / 4) {
		/* shrink the buffer to half of the size */
		n_length = array->buffer_length / 2;

		n_length = n_length < threshhold ? threshhold : n_length;
	} else {
		/* no need to change the buffer size */
		return;
	}
	dbg_assert(array->size == array->buffer_length || array->size <= array->buffer_length / 4);
	dbg_assert(array->size <= n_length/2);

	if (n_length == array->buffer_length) {
		/* in case we touch the minimum threshhold */
		return;
	}

	n_buffer = allocator_alloc(array->allocator, n_length);
	if (array->idx_start <= array->idx_end) {
		memcpy(n_buffer, array->buffer + array->idx_start, sizeof(void*) * array->size);
	} else {
		int tail_len = array->buffer_length - array->idx_end;
		int head_len = array->idx_start;
		memcpy(n_buffer, array->buffer + array->idx_start, sizeof(void*) * tail_len);
		memcpy(n_buffer + tail_len, array->buffer, sizeof(void*) * head_len);
	}

	allocator_dealloc(array->allocator, array->buffer);
	array->buffer = n_buffer;
	array->buffer_length = n_length;
	array->idx_start = 0;
	array->idx_end = array->size;
}

void oarray_destroy(Object* o) {
	struct oarray* array = (struct oarray*)o;
	allocator alc = array->allocator;
	bool join_alc = array->allocator_join_ondispose;

	oarray_clear(o);

	allocator_dealloc(array->allocator, array->buffer);
	allocator_dealloc(array->allocator, array);

	if (join_alc) {
		allocator_join(alc);
	}
}
Object* oarray_clone(const Object* o) {
	return NULL;
}
bool oarray_equals(const Object* o, const Object* other) {
	return false;
}
int oarray_compare_to(const Object* o, const Object* other) {
	return 0;
}
hashcode oarray_hashcode(const Object* o) {
	return 0;
}

void oarray_clear(Object* o) {
	struct oarray* array = (struct oarray*)o;
	int i = 0;

	for (i = 0; i < array->size; i ++) {
		int index = (array->idx_start + i) % array->buffer_length;

		array->content_traits.__destroy(array->buffer[index], (pf_dealloc)allocator_release, array->allocator);
	}

	array->size = 0;
	array->idx_end = array->idx_start;

	oarray_adjust_buffer(array);
}

void oarray_foreach(Object* o, pf_ref_process_v process, void* context) {
	struct oarray* array = (struct oarray*)o;
	int i = 0;

	for (i = 0; i < array->size; i ++) {
		int index = (array->idx_start + i) % array->buffer_length;

		process(array->buffer[index], context);;
	}
}

int oarray_size(const Object* o) {
	const struct oarray* array = (const struct oarray*)o;

	return array->size;
}

bool oarray_empty(const Object* o) {
	const struct oarray* array = (const struct oarray*)o;

	return array->size == 0;
}

const unknown* oarray_front(const Object* o) {
	const struct oarray* array = (const struct oarray*)o;

	if (array->size == 0) {
		return NULL;
	}

	return array->buffer[array->idx_start];
}

const unknown* oarray_back(const Object* o) {
	const struct oarray* array = (const struct oarray*)o;

	if (array->size == 0) {
		return NULL;
	}

	return array->buffer[array->idx_end];
}

const unknown* oarray_at(const Object* o, int index) {
	const struct oarray* array = (const struct oarray*)o;

	if (index >= 0) {
		if (index >= array->size) 
			return NULL;

		index = (array->idx_start + index) % array->buffer_length;
	}
	if (index < 0) {
		if (index < -array->size)
			return NULL;

		index = (array->idx_end + index + 1);
		if (index < 0)
			index += array->buffer_length;
		dbg_assert(index >= 0 && index < array->buffer_length);
	}


	return array->buffer[index];
}

void oarray_add_front(Object* o, const unknown* __ref) {
	struct oarray* array = (struct oarray*)o;
	array->idx_start --;
	if (array->idx_start < 0) 
		array->idx_start += array->buffer_length;

	array->buffer[array->idx_start] = array->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, array->allocator);
	array->size ++;

	oarray_adjust_buffer(array);
}

/* TODO: working from here */
void oarray_add_back(Object* o, const unknown* __ref) {
	struct oarray* array = (struct oarray*)o;

	struct oarray_node* n_node = (struct oarray_node*)
		allocator_alloc(array->allocator, sizeof(struct oarray_node));

	n_node->reference = array->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, array->allocator);

	list_insert_back(&array->sentinel, &n_node->link);
	array->size ++;
}

void oarray_remove_front(Object* o) {
	struct oarray* array = (struct oarray*)o;

	if (array->size > 0) {
		struct listlink* link    = array->sentinel.next;
		struct oarray_node* node = container_of(link, struct oarray_node, link);
		unknown* object_ref   = node->reference;

		dbg_assert(link != &array->sentinel);

		list_unlink(link);
		allocator_dealloc(array->allocator, node);

		array->content_traits.__destroy(object_ref, (pf_dealloc)allocator_release, array->allocator);

		array->size --;

		return;
	}

	dbg_assert(array->size == 0);
	dbg_assert(list_empty(&array->sentinel));

	return;
}

void oarray_remove_back(Object* o) {
	struct oarray* array = (struct oarray*)o;

	if (array->size > 0) {
		struct listlink* link    = array->sentinel.prev;
		struct oarray_node* node = container_of(link, struct oarray_node, link);
		unknown* object_ref        = node->reference;

		dbg_assert(link != &array->sentinel);

		list_unlink(link);
		allocator_dealloc(array->allocator, node);

		array->content_traits.__destroy(object_ref, (pf_dealloc)allocator_release, array->allocator);

		array->size --;
		return;
	}

	dbg_assert(array->size == 0);
	dbg_assert(list_empty(&array->sentinel));

	return;
}

bool oarray_contains(const Object* o, const unknown* __ref) {
	const struct oarray* array  = (const struct oarray*)o;
	const struct listlink* link = array->sentinel.next;

	while (link != &array->sentinel) {
		struct oarray_node* temp = container_of(link, struct oarray_node, link);

		if (array->content_traits.__equals(temp->reference, __ref)) {
			return true;
		}

		link = link->next;
	}

	return false;
}

bool oarray_remove(Object* o, const unknown* __ref) {
	struct oarray* array  = (struct oarray*)o;
	struct listlink* link = array->sentinel.next;

	while (link != &array->sentinel) {
		struct oarray_node* temp = container_of(link, struct oarray_node, link);

		if (array->content_traits.__equals(temp->reference, __ref)) {
			break;
		}

		link = link->next;
	}

	if (link != &array->sentinel) {
		struct oarray_node* node = container_of(link, struct oarray_node, link);
		unknown* object_ref = node->reference;

		list_unlink(link);
		allocator_dealloc(array->allocator, node);
		array->content_traits.__destroy(object_ref, (pf_dealloc)allocator_release, array->allocator);

		array->size --;
		return true;
	}
	return false;
}


/* initialize all part of an iterator except the __current position */
static void oarray_itr_com_init(struct oarray_itr* itr, struct oarray* list) {
	itr->__offset = itr;
	itr->__cast   = oarray_itr_cast;

	itr->__iftable[itr_interface_iobject].__offset = (address)itr_interface_iobject;
	itr->__iftable[itr_interface_iobject].__vtable = (void*)&__array_itr_iobject_vtable;
	itr->__iftable[itr_interface_iterator].__offset = (address)itr_interface_iterator;
	itr->__iftable[itr_interface_iterator].__vtable = (void*)&__array_itr_vtable;

	itr->container = list;
	itr->allocator = list->allocator;
	/* itr->__current = NULL; */
}

const_iterator oarray_itr_begin(const Object* o) {
	struct oarray* array = (struct oarray*)o;

	/* if the list is empty, we just return the sentinel node */
	array->itr_begin.current = array->sentinel.next;

	return (const_iterator)&array->itr_begin;
}

const_iterator oarray_itr_end(const Object* o) {
	struct oarray* array = (struct oarray*)o;

	array->itr_end.current = &array->sentinel;

	return (const_iterator)&array->itr_end;
}

iterator oarray_itr_create(const Object* o, itr_pos pos) {
	struct oarray* array = (struct oarray*)o;
	struct oarray_itr* n_itr = (struct oarray_itr*)
		allocator_alloc(array->allocator, sizeof(struct oarray_itr));

	oarray_itr_com_init(n_itr, array);

	if (pos == itr_begin) {
		/* if the list is empty, we just return the sentinel node */
		n_itr->current = array->sentinel.next;
	}
	else if (pos == itr_end) {
		/* the end iterator is the sentinel node, since 
		 * (begin, end) represents [begin, end) */
		n_itr->current = &array->sentinel;
	}
	else {
		dbg_assert(false);
	}

	return (iterator)n_itr;
}

void oarray_itr_assign(const Object* o, iterator __itr, itr_pos pos) {
	struct oarray* array = (struct oarray*)o;
	struct oarray_itr* itr = (struct oarray_itr*)__itr;

	dbg_assert(itr->__cast == oarray_itr_cast);
	dbg_assert(itr->container == array);
	dbg_assert(itr->current != NULL);

	oarray_itr_com_init(itr, array);

	if (pos == itr_begin) {
		/* if the list is empty, we just return the sentinel node */
		itr->current = array->sentinel.next;
	}
	else if (pos == itr_end) {
		/* the end iterator is the sentinel node, since 
		 * (begin, end) represents [begin, end) */
		itr->current = &array->sentinel;
	}
	else {
		dbg_assert(false);
	}

	return;
}

void oarray_itr_find(const Object* o, iterator itr, const unknown* __ref) {
	struct oarray* array    = (struct oarray*)o;
	struct oarray_itr* oitr = (struct oarray_itr*)itr;
	struct listlink* link   = array->sentinel.next;

	/* make sure the type information is right */
	dbg_assert(itr->__iftable[itr_interface_iterator].__offset == (address)itr_interface_iterator);
	dbg_assert(itr->__iftable[itr_interface_iterator].__vtable == (void*)&__array_itr_vtable);

	dbg_assert(oitr->container == array);

	while (link != &array->sentinel) {
		struct oarray_node* temp = container_of(link, struct oarray_node, link);

		if (array->content_traits.__equals(temp->reference, __ref)) {
			break;
		}

		link = link->next;
	}

	oitr->current = link;
}

void oarray_itr_remove(Object* o, iterator itr) {
	struct oarray* array     = (struct oarray*)o;
	struct oarray_itr* oitr  = (struct oarray_itr*)itr;
	struct oarray_node* node = container_of(oitr->current, struct oarray_node, link);
	unknown* obj_ref         = node->reference;

	dbg_assert(oitr->__cast == oarray_itr_cast);
	dbg_assert(oitr->container == array);
	dbg_assert(oitr->current != NULL);

	list_unlink(&node->link);
	
	allocator_dealloc(array->allocator, node);
	array->content_traits.__destroy(obj_ref, (pf_dealloc)allocator_release, array->allocator);

	array->size --;

	/* invalidate the iterator */
	oitr->current = NULL;

	return;
}

void oarray_insert_before(Object* o, iterator itr, const unknown* __ref) {
	struct oarray* array       = (struct oarray*)o;
	struct oarray_itr* oitr    = (struct oarray_itr*)itr;
	struct oarray_node* node   = container_of(oitr->current, struct oarray_node, link);
	struct oarray_node* n_node = (struct oarray_node*)
		allocator_alloc(array->allocator, sizeof(struct oarray_node));

	dbg_assert(oitr->__cast == oarray_itr_cast);
	dbg_assert(oitr->container == array);
	dbg_assert(oitr->current != NULL);

	n_node->reference = array->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, array->allocator);
	list_link(&n_node->link, (&node->link)->prev, &node->link);

	array->size ++;
}

void oarray_insert_after(Object* o, iterator itr, const unknown* __ref) {
	struct oarray* array       = (struct oarray*)o;
	struct oarray_itr* oitr    = (struct oarray_itr*)itr;
	struct oarray_node* node   = container_of(oitr->current, struct oarray_node, link);
	struct oarray_node* n_node = (struct oarray_node*)
		allocator_alloc(array->allocator, sizeof(struct oarray_node));

	dbg_assert(oitr->__cast == oarray_itr_cast);
	dbg_assert(oitr->container == array);
	dbg_assert(oitr->current != NULL);

	n_node->reference = array->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, array->allocator);
	list_link(&n_node->link, (&node->link), (&node->link)->next);

	array->size ++;
}
