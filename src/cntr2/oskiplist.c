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

struct oslist_itr {
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
struct oslist {
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

	struct oslist_itr          itr_begin;
	struct oslist_itr          itr_end;
};

static struct iobject_vtable __oslist_iobject_vtable = {
	oslist_destroy,          /* __destroy */
	oslist_clone,            /* __clone */
	oslist_equals,           /* __equals */
	oslist_compare_to,       /* __compare_to */
	oslist_hashcode,         /* __hashcode */
};

static struct iset_vtable __oslist_iset_vtable = {
	oslist_clear,            /* __clear */
	oslist_size,             /* __size */
	oslist_empty,            /* __empty */
	oslist_insert_s,         /* __insert */
	oslist_replace_s,        /* __replace */
	oslist_contains,         /* __contains */
	oslist_remove_s,         /* __remove */

	oslist_itr_create,       /* __itr_create */
	oslist_itr_assign,       /* __itr_assign */
	oslist_itr_find,         /* __itr_find */
	oslist_itr_remove,       /* __itr_remove */
	oslist_itr_begin,        /* __itr_begin */
	oslist_itr_end           /* __itr_end */
};

static struct imset_vtable __oslist_imset_vtable = {
	oslist_clear,            /* __clear */
	oslist_size,             /* __size */
	oslist_empty,            /* __empty */
	oslist_insert_m,         /* __insert */
	oslist_contains,         /* __contains */
	oslist_count,            /* __count */
	oslist_remove_m,         /* __remove */

	oslist_itr_create,       /* __itr_create */
	oslist_itr_assign,       /* __itr_assign */
	oslist_itr_find_lower,   /* __itr_find_lower */
	oslist_itr_find_upper,   /* __itr_find_upper */
	oslist_itr_remove,       /* __itr_remove */
	oslist_itr_begin,        /* __itr_begin */
	oslist_itr_end           /* __itr_end */
};

static unknown oslist_itr_cast(unknown x, unique_id inf_id);
static unknown oslist_cast(unknown x, unique_id intf_id);

static void oslist_itr_destroy(iterator citr);
static iterator oslist_itr_clone(const_iterator citr);
static bool oslist_itr_equals(const_iterator a, const_iterator b);
static int oslist_itr_compare_to(const_iterator itr, const_iterator other);
static hashcode oslist_itr_hashcode(const_iterator itr);
static const void* oslist_itr_get_ref(const_iterator citr);
static void oslist_itr_set_ref(iterator citr, const void* n_ref);
static void oslist_itr_to_next(iterator citr);
static void oslist_itr_to_prev(iterator citr);

static struct iobject_vtable __oslist_itr_iobject_vtable = {
	oslist_itr_destroy,      /* __destroy */
	oslist_itr_clone,        /* __clone   */
	oslist_itr_equals,       /* __equals  */
	oslist_itr_compare_to,   /* __compare_to */
	oslist_itr_hashcode
};

static struct itr_bidirectional_vtable __oslist_itr_vtable = {
	oslist_itr_get_ref,      /* __get_ref */
	oslist_itr_set_ref,      /* __set_ref */
	oslist_itr_to_next,      /* __to_next */
	oslist_itr_to_prev       /* __to_prev */
};


static void oslist_itr_destroy(object citr) {
	struct oslist_itr* itr = (struct oslist_itr*)citr;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == oslist_itr_cast);

	/* destroy itself */
	allocator_dealloc(itr->allocator, itr);
}

static iterator oslist_itr_clone(const_iterator citr) {
	struct oslist_itr* itr = (struct oslist_itr*)citr;
	struct oslist_itr* n_itr = NULL;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == oslist_itr_cast);

	/* destroy itself */
	n_itr = (struct oslist_itr*)allocator_alloc(itr->allocator, sizeof(struct oslist_itr));

	memcpy (n_itr, itr, sizeof(struct oslist_itr));
	/* NOTE: this is error prone */
	n_itr->__offset = n_itr;

	return (iterator)n_itr;
}

static bool oslist_itr_equals(const_iterator a, const_iterator b) {
	const struct oslist_itr* itr_a = (const struct oslist_itr*)a;
	const struct oslist_itr* itr_b = (const struct oslist_itr*)b;

	dbg_assert(__is_object((unknown)a));
	dbg_assert(__is_object((unknown)b));
	dbg_assert(itr_a->__cast == oslist_itr_cast);
	dbg_assert(itr_b->__cast == oslist_itr_cast);

	return itr_a->current == itr_b->current;
}

static int oslist_itr_compare_to(const_iterator itr, const_iterator other) {
	// TODO
	return 0;
}
static hashcode oslist_itr_hashcode(const_iterator itr) {
	// TODO
	return 0;
}

static const void* oslist_itr_get_ref(const_iterator citr) {
	const struct oslist_itr* itr = (const struct oslist_itr*)citr;
	const struct skip_link* link    = itr->current;

	dbg_assert(itr->__cast == oslist_itr_cast);
	dbg_assert(itr->current != NULL);

	return skip_link_getref(link);
}

static void oslist_itr_set_ref(iterator citr, const void* n_ref) {
	/* skiplist does not permit to set ref, which would destroy the inner data structure. */
	unused(citr);
	unused(n_ref);

	dbg_assert(false);

	return;
}

static void oslist_itr_to_next(object citr) {
	struct oslist_itr* itr    = (struct oslist_itr*)citr;

	dbg_assert(itr->__cast == oslist_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = skip_link_next(itr->current);
}

static void oslist_itr_to_prev(object citr) {
	struct oslist_itr* itr = (struct oslist_itr*)citr;

	dbg_assert(itr->__cast == oslist_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = skip_link_prev(itr->current);
}

static unknown oslist_cast(unknown x, unique_id intf_id) {
	struct oslist* o = (struct oslist*)x;

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

static unknown oslist_itr_cast(unknown x, unique_id inf_id) {
	struct oslist_itr* itr = (struct oslist_itr*)x;

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

static void oslist_itr_com_init(struct oslist_itr* itr, struct oslist* list);
object oslist_create_internal(unknown_traits content_traits, allocator alc) {
	struct oslist* oskiplist = NULL;
	bool managed_allocator = false;

	if (alc == NULL) {
		alc = allocator_mpool_spawn(__global_default_allocator, 40);
		managed_allocator = true;
	}

	oskiplist = (struct oslist*)allocator_alloc(alc, sizeof(struct oslist));

	oskiplist->__offset = oskiplist;
	oskiplist->__cast   = oslist_cast;
	
	oskiplist->__iftable[e_object].__offset = (address)e_object;
	oskiplist->__iftable[e_object].__vtable = &__oslist_iobject_vtable;
	oskiplist->__iftable[e_set].__offset = (address)e_set;
	oskiplist->__iftable[e_set].__vtable = &__oslist_iset_vtable;
	oskiplist->__iftable[e_mset].__offset = (address)e_mset;
	oskiplist->__iftable[e_mset].__vtable = &__oslist_imset_vtable;

	oskiplist->size      = 0;

	dbg_assert(content_traits.__compare_to != NULL);
	oskiplist->content_traits = content_traits;

	oskiplist->driver_skiplist  = skiplist_create_a(content_traits.__compare_to, (pf_alloc)allocator_acquire, (pf_dealloc)allocator_release, alc);

	oskiplist->allocator = alc;
	oskiplist->allocator_join_ondispose = managed_allocator;

	/* initialize begin/end iterators, the position is reassigned when each query */
	oslist_itr_com_init(&oskiplist->itr_begin, oskiplist);
	oslist_itr_com_init(&oskiplist->itr_end, oskiplist);

	return (object)oskiplist;
}

object oslist_create(unknown_traits content_traits, allocator alc) {
	return oslist_create_internal(content_traits, alc);
}

object cntr_create_oskiplist(unknown_traits content_traits) {
	return oslist_create_internal(content_traits, __global_default_allocator);
}
object cntr_create_oskiplist_a(unknown_traits content_traits, allocator alc) {
	return oslist_create_internal(content_traits, alc);
}

void oslist_destroy(object o) {
	struct oslist* oskiplist = (struct oslist*)o;
	allocator alc = oskiplist->allocator;
	bool join_alc = oskiplist->allocator_join_ondispose;

	oslist_clear(o);
	skiplist_destroy(oskiplist->driver_skiplist);
	allocator_dealloc(alc, oskiplist);

	if (join_alc) {
		allocator_join(alc);
	}
}

object oslist_clone(const_object o) {
	return NULL;
}
bool oslist_equals(const_object o, const_object other) {
	return false;
}
int oslist_compare_to(const_object o, const_object other) {
	return 1;
}
hashcode oslist_hashcode(const_object o) {
	return (hashcode)NULL;
}

void oslist_reference_dispose(const void* __ref, void* context) {
	struct oslist* oslist = (struct oslist*)context;

	oslist->content_traits.__destroy(__ref, (pf_dealloc)allocator_release, oslist->allocator);
}

void oslist_clear(object o) {
	struct oslist* oskiplist = (struct oslist*)o;

	skiplist_foreach(oskiplist->driver_skiplist, oslist_reference_dispose, oskiplist);
	skiplist_clear(oskiplist->driver_skiplist);

	oskiplist->size = 0;
}

int oslist_size(const_object o) {
	struct oslist* oskiplist = (struct oslist*)o;

	return oskiplist->size;
}

bool oslist_empty(const_object o) {
	struct oslist* oskiplist = (struct oslist*)o;
	return oskiplist->size == 0;
}

/* initialize all part of an iterator except the __current position */
static void oslist_itr_com_init(struct oslist_itr* itr, struct oslist* list) {
	itr->__offset = itr;
	itr->__cast   = oslist_itr_cast;

	itr->__iftable[itr_interface_iobject].__offset = (address)itr_interface_iobject;
	itr->__iftable[itr_interface_iobject].__vtable = (unknown)&__oslist_itr_iobject_vtable;
	itr->__iftable[itr_interface_iterator].__offset = (address)itr_interface_iterator;
	itr->__iftable[itr_interface_iterator].__vtable = (unknown)&__oslist_itr_vtable;

	itr->allocator = list->allocator;
	/* itr->__current = NULL; */
}

const_iterator oslist_itr_begin(const_object o) {
	struct oslist* olist = (struct oslist*)o;

	olist->itr_begin.current = skiplist_first(olist->driver_skiplist);

	return (iterator)&olist->itr_begin;
}

const_iterator oslist_itr_end(const_object o) {
	struct oslist* olist = (struct oslist*)o;

	olist->itr_end.current = skiplist_sent(olist->driver_skiplist);

	return (iterator)&olist->itr_end;
}

iterator oslist_itr_create(const_object o, itr_pos pos) {
	struct oslist* olist = (struct oslist*)o;
	struct oslist_itr* n_itr = (struct oslist_itr*)
		allocator_alloc(olist->allocator, sizeof(struct oslist_itr));

	oslist_itr_com_init(n_itr, olist);

	if (pos == itr_begin) {
		n_itr->current = skiplist_first(olist->driver_skiplist);
	}
	else {
		/* __sentinel will be the maximum element in the tree */
		n_itr->current = skiplist_sent(olist->driver_skiplist);
	}
	
	return (object)n_itr;
}

void oslist_itr_assign(const_object o, iterator itr, itr_pos pos) {
	struct oslist* olist = (struct oslist*)o;
	struct oslist_itr* n_itr = (struct oslist_itr*)itr;

	oslist_itr_com_init(n_itr, olist);

	if (pos == itr_begin) {
		n_itr->current = skiplist_first(olist->driver_skiplist);
	}
	else {
		/* __sentinel will be the maximum element in the tree */
		n_itr->current = skiplist_sent(olist->driver_skiplist);
	}
}
void oslist_itr_find(const_object o, iterator itr, const void* __ref) {
	struct oslist* olist      = (struct oslist*)o;
	struct oslist_itr* oitr   = (struct oslist_itr*)itr;
	const struct skip_link* link = NULL;

	link = skiplist_search(olist->driver_skiplist, __ref);

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[itr_interface_iterator].__offset == (address)itr_interface_iterator);
	dbg_assert(itr->__iftable[itr_interface_iterator].__vtable == (unknown)&__oslist_itr_vtable);

	oitr->current = link;
}

void oslist_itr_find_lower(const_object o, iterator itr, const void* __ref) {
	struct oslist* oskiplist = (struct oslist*)o;
	struct oslist_itr* oitr  = (struct oslist_itr*)itr;
	const struct skip_link* link = NULL;

	link = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greaterorequal);

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[itr_interface_iterator].__offset == (address)itr_interface_iterator);
	dbg_assert(itr->__iftable[itr_interface_iterator].__vtable == (unknown)&__oslist_itr_vtable);

	oitr->current = link;
}

void oslist_itr_find_upper(const_object o, iterator itr, const void* __ref) {
	struct oslist* oskiplist = (struct oslist*)o;
	struct oslist_itr* oitr  = (struct oslist_itr*)itr;
	const struct skip_link* link = NULL;

	link = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greater);

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[itr_interface_iterator].__offset == (address)itr_interface_iterator);
	dbg_assert(itr->__iftable[itr_interface_iterator].__vtable == (unknown)&__oslist_itr_vtable);

	oitr->current = link;
}

void oslist_insert_s(object o, const_unknown __ref) {
	struct oslist* oskiplist     = (struct oslist*)o;
	const_unknown managed_ref = oskiplist->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, oskiplist->allocator);
	bool res = skiplist_insert_s(oskiplist->driver_skiplist, managed_ref);

	if (res == true)
		oskiplist->size ++;
	else 
		oskiplist->content_traits.__destroy(managed_ref, (pf_dealloc)allocator_release, oskiplist->allocator);
}

void oslist_replace_s(object o, const_unknown __ref) {
	struct oslist* oskiplist     = (struct oslist*)o;
	const_unknown managed_ref = oskiplist->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, oskiplist->allocator);
	bool res = false;
	const_unknown replaced_ref = NULL;

	replaced_ref = skiplist_replace_s(oskiplist->driver_skiplist, managed_ref);

	if (replaced_ref == NULL)
		oskiplist->size ++;
	else 
		oskiplist->content_traits.__destroy(replaced_ref, (pf_dealloc)allocator_release, oskiplist->allocator);
}

void oslist_insert_m(object o, const_unknown __ref) {
	struct oslist* oskiplist = (struct oslist*)o;
	const_unknown managed_ref = oskiplist->content_traits.__clone(__ref, (pf_alloc)allocator_acquire, oskiplist->allocator);

	skiplist_insert(oskiplist->driver_skiplist, managed_ref);

	oskiplist->size ++;
	return;
}

bool oslist_contains(const_object o, const_unknown __ref) {
	struct oslist* oskiplist   = (struct oslist*)o;

	return skiplist_contains(oskiplist->driver_skiplist, __ref);
}

int oslist_count(const_object o, const void* __ref) {
	struct oslist* oskiplist = (struct oslist*)o;
	const struct skip_link* lb = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greaterorequal);
	const struct skip_link* ub = skiplist_search_v(oskiplist->driver_skiplist, __ref, skiplist_min_greater);
	int count = 0;
	
	while (lb != ub) {
		count ++;
		lb = skip_link_next(lb);
	}

	return count;
}

bool oslist_remove_s(object o, const_unknown __ref) {
	struct oslist* oskiplist   = (struct oslist*)o;
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

int oslist_remove_m(object o, const_unknown __ref) {
	struct oslist* oskiplist   = (struct oslist*)o;
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

void oslist_itr_remove(object o, iterator itr) {
	struct oslist* oskiplist = (struct oslist*)o;
	struct oslist_itr* oitr  = (struct oslist_itr*)itr;
	struct skip_link* link      = (struct skip_link*)oitr->current;
	const void* obj_ref         = skip_link_getref(link);

	dbg_assert(oitr->__cast == oslist_itr_cast);
	dbg_assert(oitr->current != NULL);

	skiplist_remove_link(oskiplist->driver_skiplist, link);
	oskiplist->content_traits.__destroy(obj_ref, (pf_dealloc)allocator_release, oskiplist->allocator);

	oskiplist->size --;

	/* invalidate the iterator */
	oitr->current = NULL;
}

