#include <string.h>

#include <cntr2/iobject.h>
#include <cntr2/iset.h>
#include <cntr2/iitr.h>
#include <cntr2/ifactory.h>
#include <cntr2/oskiplist.h>
#include <cntr2/oallocator.h>

#include <util/skiplist.h>

/* this module defines a left-lean red black tree container, which implements iset interface. */

enum skiplist_interfaces {
	e_object,
	e_set,
	e_mset,
	e_l_count
};

struct oskiplist_itr {
	address                       __offset;
	pf_cast                       __cast;

	/* there is always one interface to implement, since the interface is inherited */
	struct base_interface          __iftable[itr_interface_count];

	/* the iterator will never alloc memory, when acquire an iterator, the container will 
	 * alloc the memory, but we should know how to delete this memory */
	allocator                     allocator;

	const struct skip_link*       current;
};

/* binary search tree */
struct oskiplist {
	address                       __offset;
	pf_cast                       __cast;
	
	struct base_interface         __iftable[e_l_count];

	struct skiplist*              driver_skiplist;

	int                           size;

	unknown_traits                content_traits;
	pf_ref_compare                ref_comp;
	pf_ref_compare_v              ref_comp_v;
	void*                         comp_context;

	/* methods to manage the inner memory use by the container */
	allocator                     allocator;
	bool                          allocator_join_ondispose;      

	struct oskiplist_itr          itr_begin;
	struct oskiplist_itr          itr_end;
};

static struct iobject_vtable __oskiplist_iobject_vtable = {
	oskiplist_destroy,          /* __destroy */
	oskiplist_clone,            /* __clone */
	oskiplist_equals,           /* __equals */
	oskiplist_compare_to,       /* __compare_to */
	oskiplist_hashcode,         /* __hashcode */
};

static struct iset_vtable __oskiplist_iset_vtable = {
	oskiplist_clear,            /* __clear */
	oskiplist_size,             /* __size */
	oskiplist_empty,            /* __empty */
	oskiplist_insert_s,         /* __insert */
	oskiplist_replace_s,        /* __replace */
	oskiplist_contains,         /* __contains */
	oskiplist_remove_s,         /* __remove */

	oskiplist_itr_create,       /* __itr_create */
	oskiplist_itr_assign,       /* __itr_assign */
	oskiplist_itr_find,         /* __itr_find */
	oskiplist_itr_remove,       /* __itr_remove */
	oskiplist_itr_begin,        /* __itr_begin */
	oskiplist_itr_end           /* __itr_end */
};

static struct imset_vtable __oskiplist_imset_vtable = {
	oskiplist_clear,            /* __clear */
	oskiplist_size,             /* __size */
	oskiplist_empty,            /* __empty */
	oskiplist_insert_m,         /* __insert */
	oskiplist_contains,         /* __contains */
	oskiplist_count,            /* __count */
	oskiplist_remove_m,         /* __remove */

	oskiplist_itr_create,       /* __itr_create */
	oskiplist_itr_assign,       /* __itr_assign */
	oskiplist_itr_find_lower,   /* __itr_find_lower */
	oskiplist_itr_find_upper,   /* __itr_find_upper */
	oskiplist_itr_remove,       /* __itr_remove */
	oskiplist_itr_begin,        /* __itr_begin */
	oskiplist_itr_end           /* __itr_end */
};

static unknown oskiplist_itr_cast(unknown x, unique_id inf_id);
static unknown oskiplist_cast(unknown x, unique_id intf_id);

static void oskiplist_itr_destroy(iterator citr);
static iterator oskiplist_itr_clone(const_iterator citr);
static bool oskiplist_itr_equals(const_iterator a, const_iterator b);
static int oskiplist_itr_compare_to(const_iterator itr, const_iterator other);
static hashcode oskiplist_itr_hashcode(const_iterator itr);
static const void* oskiplist_itr_get_ref(const_iterator citr);
static void oskiplist_itr_set_ref(iterator citr, const void* n_ref);
static void oskiplist_itr_to_next(iterator citr);
static void oskiplist_itr_to_prev(iterator citr);

static struct iobject_vtable __oskiplist_itr_iobject_vtable = {
	oskiplist_itr_destroy,      /* __destroy */
	oskiplist_itr_clone,        /* __clone   */
	oskiplist_itr_equals,       /* __equals  */
	oskiplist_itr_compare_to,   /* __compare_to */
	oskiplist_itr_hashcode
};

static struct itr_bidirectional_vtable __oskiplist_itr_vtable = {
	oskiplist_itr_get_ref,      /* __get_ref */
	oskiplist_itr_set_ref,      /* __set_ref */
	oskiplist_itr_to_next,      /* __to_next */
	oskiplist_itr_to_prev       /* __to_prev */
};


static void oskiplist_itr_destroy(object citr) {
	struct oskiplist_itr* itr = (struct oskiplist_itr*)citr;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == oskiplist_itr_cast);

	/* destroy itself */
	allocator_dealloc(itr->allocator, itr);
}

static iterator oskiplist_itr_clone(const_iterator citr) {
	struct oskiplist_itr* itr = (struct oskiplist_itr*)citr;
	struct oskiplist_itr* n_itr = NULL;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == oskiplist_itr_cast);

	/* destroy itself */
	n_itr = (struct oskiplist_itr*)allocator_alloc(itr->allocator, sizeof(struct oskiplist_itr));

	memcpy (n_itr, itr, sizeof(struct oskiplist_itr));
	/* NOTE: this is error prone */
	n_itr->__offset = n_itr;

	return (iterator)n_itr;
}

static bool oskiplist_itr_equals(const_iterator a, const_iterator b) {
	const struct oskiplist_itr* itr_a = (const struct oskiplist_itr*)a;
	const struct oskiplist_itr* itr_b = (const struct oskiplist_itr*)b;

	dbg_assert(__is_object((unknown)a));
	dbg_assert(__is_object((unknown)b));
	dbg_assert(itr_a->__cast == oskiplist_itr_cast);
	dbg_assert(itr_b->__cast == oskiplist_itr_cast);

	return itr_a->current == itr_b->current;
}

static int oskiplist_itr_compare_to(const_iterator itr, const_iterator other) {
	// TODO
	return 0;
}
static hashcode oskiplist_itr_hashcode(const_iterator itr) {
	// TODO
	return 0;
}

static const void* oskiplist_itr_get_ref(const_iterator citr) {
	const struct oskiplist_itr* itr = (const struct oskiplist_itr*)citr;
	const struct skip_link* link    = itr->current;

	dbg_assert(itr->__cast == oskiplist_itr_cast);
	dbg_assert(itr->current != NULL);

	return skip_link_getref(link);
}

static void oskiplist_itr_set_ref(iterator citr, const void* n_ref) {
	/* skiplist does not permit to set ref, which would destroy the inner data structure. */
	unused(citr);
	unused(n_ref);

	dbg_assert(false);

	return;
}

static void oskiplist_itr_to_next(object citr) {
	struct oskiplist_itr* itr    = (struct oskiplist_itr*)citr;

	dbg_assert(itr->__cast == oskiplist_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = skip_link_next(itr->current);
}

static void oskiplist_itr_to_prev(object citr) {
	struct oskiplist_itr* itr = (struct oskiplist_itr*)citr;

	dbg_assert(itr->__cast == oskiplist_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = skip_link_prev(itr->current);
}

static unknown oskiplist_cast(unknown x, unique_id intf_id) {
	struct oskiplist* o = (struct oskiplist*)x;

	dbg_assert(__is_object(x));

	switch (intf_id) {
	case IOBJECT_ID:
		return (unknown)&o->__iftable[e_object];
		break;
	case ISET_ID:
		return (unknown)&o->__iftable[e_set];
		break;
	case IMSET_ID:
		return (unknown)&o->__iftable[e_mset];
		break;
	default:
		break;
	}

	return NULL;
}

static unknown oskiplist_itr_cast(unknown x, unique_id inf_id) {
	struct oskiplist_itr* itr = (struct oskiplist_itr*)x;

	dbg_assert(__is_object(itr));

	switch (inf_id) {
	case IOBJECT_ID:
		return (unknown)&itr->__iftable[itr_interface_iobject];
	case ITR_REF_ID:
	case ITR_ACC_ID:
	case ITR_FWD_ID:
	case ITR_BID_ID:
		return (unknown)&itr->__iftable[itr_interface_iterator];
	case ITR_RAC_ID:
		return NULL;
	default:
		return NULL;
	}

	return NULL;
}

static void oskiplist_itr_com_init(struct oskiplist_itr* itr, struct oskiplist* list);
object oskiplist_create_internal(unknown_traits content_traits, allocator alc) {
	struct oskiplist* oskiplist = NULL;
	bool managed_allocator = false;

	if (alc == NULL) {
		alc = allocator_mpool_spawn(__global_default_allocator, 40);
		managed_allocator = true;
	}

	oskiplist = (struct oskiplist*)allocator_alloc(alc, sizeof(struct oskiplist));

	oskiplist->__offset = oskiplist;
	oskiplist->__cast   = oskiplist_cast;
	
	oskiplist->__iftable[e_object].__offset = (address)e_object;
	oskiplist->__iftable[e_object].__vtable = &__oskiplist_iobject_vtable;
	oskiplist->__iftable[e_set].__offset = (address)e_set;
	oskiplist->__iftable[e_set].__vtable = &__oskiplist_iset_vtable;
	oskiplist->__iftable[e_mset].__offset = (address)e_mset;
	oskiplist->__iftable[e_mset].__vtable = &__oskiplist_imset_vtable;

	oskiplist->size      = 0;

	dbg_assert(content_traits.__compare_to != NULL);
	oskiplist->content_traits = content_traits;

	oskiplist->driver_skiplist  = skiplist_create_a(content_traits.__compare_to, (pf_alloc)allocator_acquire, (pf_dealloc)allocator_release, alc);

	oskiplist->allocator = alc;
	oskiplist->allocator_join_ondispose = managed_allocator;

	/* initialize begin/end iterators, the position is reassigned when each query */
	oskiplist_itr_com_init(&oskiplist->itr_begin, oskiplist);
	oskiplist_itr_com_init(&oskiplist->itr_end, oskiplist);

	return (object)oskiplist;
}

object oskiplist_create(unknown_traits content_traits, allocator alc) {
	return oskiplist_create_internal(content_traits, alc);
}

object cntr_create_oskiplist(unknown_traits content_traits) {
	return oskiplist_create_internal(content_traits, __global_default_allocator);
}
object cntr_create_oskiplist_a(unknown_traits content_traits, allocator alc) {
	return oskiplist_create_internal(content_traits, alc);
}

void oskiplist_destroy(object o) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;
	allocator alc = oskiplist->allocator;
	bool join_alc = oskiplist->allocator_join_ondispose;

	oskiplist_clear(o);
	skiplist_destroy(oskiplist->driver_skiplist);
	allocator_dealloc(alc, oskiplist);

	if (join_alc) {
		allocator_join(alc);
	}
}

object oskiplist_clone(const_object o) {
	return NULL;
}
bool oskiplist_equals(const_object o, const_object other) {
	return false;
}
int oskiplist_compare_to(const_object o, const_object other) {
	return 1;
}
hashcode oskiplist_hashcode(const_object o) {
	return (hashcode)NULL;
}

void oskiplist_reference_dispose(const void* __ref, void* context) {
	struct oskiplist* oslist = (struct oskiplist*)context;

	oslist->content_traits.__destroy(__ref, (pf_dealloc)allocator_release, oslist->allocator);
}

void oskiplist_clear(object o) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;

	skiplist_foreach(oskiplist->driver_skiplist, oskiplist_reference_dispose, oskiplist);
	skiplist_clear(oskiplist->driver_skiplist);

	oskiplist->size = 0;
}

int oskiplist_size(const_object o) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;

	return oskiplist->size;
}

bool oskiplist_empty(const_object o) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;
	return oskiplist->size == 0;
}

/* initialize all part of an iterator except the __current position */
static void oskiplist_itr_com_init(struct oskiplist_itr* itr, struct oskiplist* list) {
	itr->__offset = itr;
	itr->__cast   = oskiplist_itr_cast;

	itr->__iftable[itr_interface_iobject].__offset = (address)itr_interface_iobject;
	itr->__iftable[itr_interface_iobject].__vtable = (unknown)&__oskiplist_itr_iobject_vtable;
	itr->__iftable[itr_interface_iterator].__offset = (address)itr_interface_iterator;
	itr->__iftable[itr_interface_iterator].__vtable = (unknown)&__oskiplist_itr_vtable;

	itr->allocator = list->allocator;
	/* itr->__current = NULL; */
}

const_iterator oskiplist_itr_begin(const_object o) {
	struct oskiplist* olist = (struct oskiplist*)o;

	olist->itr_begin.current = skiplist_first(olist->driver_skiplist);

	return (iterator)&olist->itr_begin;
}

const_iterator oskiplist_itr_end(const_object o) {
	struct oskiplist* olist = (struct oskiplist*)o;

	olist->itr_end.current = skiplist_sent(olist->driver_skiplist);

	return (iterator)&olist->itr_end;
}

iterator oskiplist_itr_create(const_object o, itr_pos pos) {
	struct oskiplist* olist = (struct oskiplist*)o;
	struct oskiplist_itr* n_itr = (struct oskiplist_itr*)
		allocator_alloc(olist->allocator, sizeof(struct oskiplist_itr));

	oskiplist_itr_com_init(n_itr, olist);

	if (pos == itr_begin) {
		n_itr->current = skiplist_first(olist->driver_skiplist);
	}
	else {
		/* __sentinel will be the maximum element in the tree */
		n_itr->current = skiplist_sent(olist->driver_skiplist);
	}
	
	return (object)n_itr;
}

void oskiplist_itr_assign(const_object o, iterator itr, itr_pos pos) {
	struct oskiplist* olist = (struct oskiplist*)o;
	struct oskiplist_itr* n_itr = (struct oskiplist_itr*)itr;

	oskiplist_itr_com_init(n_itr, olist);

	if (pos == itr_begin) {
		n_itr->current = skiplist_first(olist->driver_skiplist);
	}
	else {
		/* __sentinel will be the maximum element in the tree */
		n_itr->current = skiplist_sent(olist->driver_skiplist);
	}
}
void oskiplist_itr_find(const_object o, iterator itr, const void* __ref) {
	struct oskiplist* olist      = (struct oskiplist*)o;
	struct oskiplist_itr* oitr   = (struct oskiplist_itr*)itr;
	const struct skip_link* link = NULL;

	link = skiplist_search(olist->driver_skiplist, __ref);

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[itr_interface_iterator].__offset == (address)itr_interface_iterator);
	dbg_assert(itr->__iftable[itr_interface_iterator].__vtable == (unknown)&__oskiplist_itr_vtable);

	oitr->current = link;
}

void oskiplist_itr_find_lower(const_object o, iterator itr, const void* __ref) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;
	struct oskiplist_itr* oitr  = (struct oskiplist_itr*)itr;
	const struct skip_link* link = NULL;

	link = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greaterorequal);

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[itr_interface_iterator].__offset == (address)itr_interface_iterator);
	dbg_assert(itr->__iftable[itr_interface_iterator].__vtable == (unknown)&__oskiplist_itr_vtable);

	oitr->current = link;
}

void oskiplist_itr_find_upper(const_object o, iterator itr, const void* __ref) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;
	struct oskiplist_itr* oitr  = (struct oskiplist_itr*)itr;
	const struct skip_link* link = NULL;

	link = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greater);

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[itr_interface_iterator].__offset == (address)itr_interface_iterator);
	dbg_assert(itr->__iftable[itr_interface_iterator].__vtable == (unknown)&__oskiplist_itr_vtable);

	oitr->current = link;
}

void oskiplist_insert_s(object o, const_unknown __ref) {
	struct oskiplist* oskiplist     = (struct oskiplist*)o;
	const_unknown managed_ref = oskiplist->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, oskiplist->allocator);
	bool res = skiplist_insert_s(oskiplist->driver_skiplist, managed_ref);

	if (res == true)
		oskiplist->size ++;
	else 
		oskiplist->content_traits.__destroy(managed_ref, (pf_dealloc)allocator_release, oskiplist->allocator);
}

void oskiplist_replace_s(object o, const_unknown __ref) {
	struct oskiplist* oskiplist     = (struct oskiplist*)o;
	const_unknown managed_ref = oskiplist->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, oskiplist->allocator);
	bool res = false;
	const_unknown replaced_ref = NULL;

	replaced_ref = skiplist_replace_s(oskiplist->driver_skiplist, managed_ref);

	if (replaced_ref == NULL)
		oskiplist->size ++;
	else 
		oskiplist->content_traits.__destroy(replaced_ref, (pf_dealloc)allocator_release, oskiplist->allocator);
}

void oskiplist_insert_m(object o, const_unknown __ref) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;
	const_unknown managed_ref = oskiplist->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, oskiplist->allocator);

	skiplist_insert(oskiplist->driver_skiplist, managed_ref);

	oskiplist->size ++;
	return;
}

bool oskiplist_contains(const_object o, const_unknown __ref) {
	struct oskiplist* oskiplist   = (struct oskiplist*)o;

	return skiplist_contains(oskiplist->driver_skiplist, __ref);
}

int oskiplist_count(const_object o, const void* __ref) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;
	const struct skip_link* lb = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greaterorequal);
	const struct skip_link* ub = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greater);
	int count = 0;
	
	while (lb != ub) {
		count ++;
		lb = skip_link_next(lb);
	}

	return count;
}

bool oskiplist_remove_s(object o, const_unknown __ref) {
	struct oskiplist* oskiplist   = (struct oskiplist*)o;
	struct skip_link* slink = (struct skip_link*)skiplist_search(oskiplist->driver_skiplist, __ref);

	if (slink != skiplist_sent(oskiplist->driver_skiplist)) {
		dbg_assert(oskiplist->content_traits.__compare_to(__ref, skip_link_getref(slink)) == 0);
		oskiplist->content_traits.__destroy(skip_link_getref(slink), (pf_dealloc)allocator_release, oskiplist->allocator);
		skiplist_remove_link(oskiplist->driver_skiplist, slink);
		oskiplist->size --;
		return true;
	}

	return false;
}

int oskiplist_remove_m(object o, const_unknown __ref) {
	struct oskiplist* oskiplist   = (struct oskiplist*)o;
	struct skip_link* slink = (struct skip_link*)skiplist_search(oskiplist->driver_skiplist, __ref);
	int count = 0;

	while (slink != skiplist_sent(oskiplist->driver_skiplist)) {
		oskiplist->content_traits.__destroy(skip_link_getref(slink), (pf_dealloc)allocator_release, oskiplist->allocator);
		skiplist_remove_link(oskiplist->driver_skiplist, slink);
		oskiplist->size --;
		count ++;

		slink = (struct skip_link*)skiplist_search(oskiplist->driver_skiplist, __ref);
	}

	return count;
}

void oskiplist_itr_remove(object o, iterator itr) {
	struct oskiplist* oskiplist = (struct oskiplist*)o;
	struct oskiplist_itr* oitr  = (struct oskiplist_itr*)itr;
	struct skip_link* link      = (struct skip_link*)oitr->current;
	const void* obj_ref         = skip_link_getref(link);

	dbg_assert(oitr->__cast == oskiplist_itr_cast);
	dbg_assert(oitr->current != NULL);

	skiplist_remove_link(oskiplist->driver_skiplist, link);
	oskiplist->content_traits.__destroy(obj_ref, (pf_dealloc)allocator_release, oskiplist->allocator);

	oskiplist->size --;

	/* invalidate the iterator */
	oitr->current = NULL;
}

