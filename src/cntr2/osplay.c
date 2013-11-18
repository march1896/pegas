#include <string.h>

#include <cntr2/iobject.h>
#include <cntr2/iset.h>
#include <cntr2/iitr.h>
#include <cntr2/ifactory.h>
#include <cntr2/osplay.h>
#include <cntr2/oallocator.h>

#include <util/splay_link.h>

/* this module defines a left-lean red black tree container, which implements iset interface. */

enum splay_interfaces {
	e_object,
	e_set,
	e_mset,
	e_l_count
};

struct osplay_node {
	struct splay_link             link;

	const void*                   reference;
};

struct osplay_itr {
	address                       __offset;
	pf_cast                       __cast;

	/* there is always one interface to implement, since the interface is inherited */
	struct base_interface         __iftable[1];

	/* the iterator will never alloc memory, when acquire an iterator, the container will 
	 * alloc the memory, but we should know how to delete this memory */
	allocator                     allocator;

	struct splay_link*            current;
};

/* binary search tree */
struct osplay {
	address                       __offset;
	pf_cast                       __cast;
	
	struct base_interface         __iftable[e_l_count];

	/* just a sentinel to represent the end of the tree, the maximum element of the tree */
	struct splay_link             sentinel;
	/* __root == __sentinel.left */
	struct splay_link*            root;

	int                           size;

	pf_ref_compare                ref_comp;    /* only one of the compare functions takes effect */
	pf_ref_compare_v              ref_comp_v;
	void*                         comp_context;

	/* methods to manage the inner memory use by the container */
	allocator                     allocator;
	bool                          allocator_join_ondispose;      

	struct osplay_itr             itr_begin;
	struct osplay_itr             itr_end;
};

static struct iobject_vtable __iobject_vtable = {
	splayset_destroy,          /* __destroy */
	splayset_clone,            /* __clone */
	splayset_equals,           /* __equals */
	splayset_compare_to,       /* __compare_to */
	splayset_hashcode,         /* __hashcode */
};

static struct iset_vtable __iset_vtable = {
	splayset_clear,            /* __clear */
	splayset_clear_v,          /* __clear_v */
	splayset_size,             /* __size */
	splayset_empty,            /* __empty */
	splayset_insert_s,         /* __insert */
	splayset_contains,         /* __contains */
	splayset_remove,           /* __remove */

	splayset_itr_create,       /* __itr_create */
	splayset_itr_assign,       /* __itr_assign */
	splayset_itr_find_s,         /* __itr_find */
	splayset_itr_remove,       /* __itr_remove */
	splayset_itr_begin,        /* __itr_begin */
	splayset_itr_end           /* __itr_end */
};

static struct imset_vtable __imset_vtable = {
	splayset_clear,            /* __clear */
	splayset_clear_v,          /* __clear_v */
	splayset_size,             /* __size */
	splayset_empty,            /* __empty */
	splayset_insert_m,         /* __insert */
	splayset_contains,         /* __contains */
	splayset_count_m,          /* __count */
	splayset_remove,           /* __remove */

	splayset_itr_create,       /* __itr_create */
	splayset_itr_assign,       /* __itr_assign */
	splayset_itr_find_lower_m, /* __itr_find_lower */
	splayset_itr_find_upper_m, /* __itr_find_upper */
	splayset_itr_remove,       /* __itr_remove */
	splayset_itr_begin,        /* __itr_begin */
	splayset_itr_end           /* __itr_end */
};

static unknown osplay_itr_cast(unknown x, unique_id inf_id);
static unknown osplay_cast(unknown x, unique_id intf_id);

static void osplay_itr_destroy(iterator citr);
static iterator osplay_itr_clone(const_iterator citr);
static bool osplay_itr_equals(const_iterator a, const_iterator b);
static const void* osplay_itr_get_ref(const_iterator citr);
static void osplay_itr_set_ref(iterator citr, const void* n_ref);
static void osplay_itr_to_next(iterator citr);
static void osplay_itr_to_prev(iterator citr);

static struct itr_bidirectional_vtable __itr_vtable = {
	osplay_itr_destroy,      /* __destroy */
	osplay_itr_clone,        /* __clone   */
	osplay_itr_equals,       /* __equals  */
	osplay_itr_get_ref,      /* __get_ref */
	osplay_itr_set_ref,      /* __set_ref */
	osplay_itr_to_next,      /* __to_next */
	osplay_itr_to_prev       /* __to_prev */
};


static void osplay_itr_destroy(object citr) {
	struct osplay_itr* itr = (struct osplay_itr*)citr;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == osplay_itr_cast);

	/* destroy itself */
	allocator_dealloc(itr->allocator, itr);
}

static iterator osplay_itr_clone(const_iterator citr) {
	struct osplay_itr* itr = (struct osplay_itr*)citr;
	struct osplay_itr* n_itr = NULL;

	dbg_assert(__is_object(citr));
	dbg_assert(itr->__cast == osplay_itr_cast);

	/* destroy itself */
	n_itr = (struct osplay_itr*)allocator_alloc(itr->allocator, sizeof(struct osplay_itr));

	memcpy (n_itr, itr, sizeof(struct osplay_itr));
	/* TODO: this is error prone */
	n_itr->__offset = n_itr;

	return (iterator)n_itr;
}

static bool osplay_itr_equals(const_iterator a, const_iterator b) {
	const struct osplay_itr* itr_a = (const struct osplay_itr*)a;
	const struct osplay_itr* itr_b = (const struct osplay_itr*)b;

	dbg_assert(__is_object((unknown)a));
	dbg_assert(__is_object((unknown)b));
	dbg_assert(itr_a->__cast == osplay_itr_cast);
	dbg_assert(itr_b->__cast == osplay_itr_cast);

	return itr_a->current == itr_b->current;
}

static const void* osplay_itr_get_ref(const_iterator citr) {
	const struct osplay_itr* itr   = (const struct osplay_itr*)citr;
	const struct osplay_node* node = NULL;

	dbg_assert(itr->__cast == osplay_itr_cast);
	dbg_assert(itr->current != NULL);

	node = container_of(itr->current, struct osplay_node, link);
	return node->reference;
}

static void osplay_itr_set_ref(iterator citr, const void* n_ref) {
	/* splay does not permit to set ref, which would destroy the inner data structure. */
	/*
	struct osplay_itr* itr   = (struct osplay_itr*)citr;
	struct osplay_node* node = NULL;

	dbg_assert(itr->__cast == osplay_itr_cast);
	dbg_assert(itr->__current != NULL);

	node = container_of(itr->__current, struct osplay_node, link);
	node->reference = n_ref;
	*/

	unused(citr);
	unused(n_ref);

	dbg_assert(false);

	return;
}

static void osplay_itr_to_next(object citr) {
	struct osplay_itr* itr = (struct osplay_itr*)citr;

	dbg_assert(itr->__cast == osplay_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = splay_successor(itr->current, false);
}

static void osplay_itr_to_prev(object citr) {
	struct osplay_itr* itr = (struct osplay_itr*)citr;

	dbg_assert(itr->__cast == osplay_itr_cast);
	dbg_assert(itr->current != NULL);

	itr->current = splay_predesessor(itr->current, false);
}

static unknown osplay_cast(unknown x, unique_id intf_id) {
	struct osplay* o = (struct osplay*)x;

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

static unknown osplay_itr_cast(unknown x, unique_id inf_id) {
	struct osplay_itr* itr = (struct osplay_itr*)x;

	dbg_assert(__is_object(itr));

	switch (inf_id) {
	case ITR_BAS_ID:
	case ITR_REF_ID:
	case ITR_ACC_ID:
	case ITR_FWD_ID:
	case ITR_BID_ID:
		return (unknown)&itr->__iftable[0];
	case ITR_RAC_ID:
		return NULL;
	default:
		return NULL;
	}

	return NULL;
}

static int osplay_compare_c(const struct splay_link* a, const struct splay_link* b, void* param) {
	pf_ref_compare ref_comp = (pf_ref_compare)param;

	struct osplay_node* node_a = container_of(a, struct osplay_node, link);
	struct osplay_node* node_b = container_of(b, struct osplay_node, link);

	return ref_comp(node_a->reference, node_b->reference);
}

struct comp_pack {
	pf_ref_compare_v comp_v;
	void*            context;
};

static int osplay_compare_v(const struct splay_link* a, const struct splay_link* b, void* param) {
	struct comp_pack* pack = (struct comp_pack*)param;
	pf_ref_compare_v ref_comp_v = pack->comp_v;
	void*            context    = pack->context;

	struct osplay_node* node_a = container_of(a, struct osplay_node, link);
	struct osplay_node* node_b = container_of(b, struct osplay_node, link);

	return ref_comp_v(node_a->reference, node_b->reference, context);
}

static void osplay_itr_com_init(struct osplay_itr* itr, struct osplay* list);
static object splayset_create_internal(pf_ref_compare comp, pf_ref_compare_v compv, void* cp_context, allocator alc) {
	struct osplay* osplay = NULL;
	bool managed_allocator = false;

	if (alc == NULL) {
		alc = allocator_mpool_spawn(__global_default_allocator, 10);
		managed_allocator = true;
	}

	osplay = (struct osplay*)allocator_alloc(alc, sizeof(struct osplay));

	osplay->__offset = osplay;
	osplay->__cast   = osplay_cast;
	
	osplay->__iftable[e_object].__offset = (address)e_object;
	osplay->__iftable[e_object].__vtable = &__iobject_vtable;
	osplay->__iftable[e_set].__offset = (address)e_set;
	osplay->__iftable[e_set].__vtable = &__iset_vtable;
	osplay->__iftable[e_mset].__offset = (address)e_mset;
	osplay->__iftable[e_mset].__vtable = &__imset_vtable;

	osplay->size      = 0;

	if (comp != NULL) {
		osplay->ref_comp  = comp;

		//dbg_assert(compv == NULL);
		osplay->ref_comp_v = NULL;
		osplay->comp_context = NULL;
	} else {
		dbg_assert(compv != NULL);
		osplay->ref_comp_v = compv;
		osplay->comp_context = cp_context;

		osplay->ref_comp = NULL;
	}
	
	osplay->root      = NULL;
	osplay->sentinel.left   = NULL;
	osplay->sentinel.right  = NULL;
	osplay->sentinel.parent = NULL;

	osplay->allocator = alc;
	osplay->allocator_join_ondispose = managed_allocator;

	/* initialize begin/end iterators, the position is reassigned when each query */
	osplay_itr_com_init(&osplay->itr_begin, osplay);
	osplay_itr_com_init(&osplay->itr_end, osplay);

	return (object)osplay;
}

object splayset_create(pf_ref_compare ref_compare, allocator alc) {
	return splayset_create_internal(ref_compare, NULL, NULL, alc);
}
object splayset_create_v(pf_ref_compare_v compv, void* cp_context, allocator alc) {
	return splayset_create_internal(NULL, compv, cp_context, alc);
}

/* from ifactory.h  */
object cntr_create_osplay(pf_ref_compare comp) {
	return splayset_create(comp, __global_default_allocator);
}
object cntr_create_osplay_a(pf_ref_compare comp, allocator alc) {
	return splayset_create(comp, alc);
}
object cntr_create_osplay_v(pf_ref_compare_v comp_v, void* comp_context) {
	return splayset_create_v(comp_v, comp_context, __global_default_allocator);
}
object cntr_create_osplay_va(pf_ref_compare_v comp_v, void* comp_context, allocator alc) {
	return splayset_create_v(comp_v, comp_context, alc);
}

void splayset_destroy(object o) {
	struct osplay* osplay = (struct osplay*)o;
	allocator alc = osplay->allocator;
	bool join_alc = osplay->allocator_join_ondispose;

	splayset_clear(o);

	allocator_dealloc(alc, osplay);

	if (join_alc) {
		allocator_join(alc);
	}
}

object splayset_clone(const_object o) {
	return NULL;
}
bool splayset_equals(const_object o, const_object other) {
	return false;
}
int splayset_compare_to(const_object o, const_object other) {
	return 1;
}
hashcode splayset_hashcode(const_object o) {
	return (hashcode)NULL;
}

typedef void (*pf_per_link_operation)(struct splay_link* link, void* param);
static void splay_traverse(struct splay_link* cur, pf_per_link_operation cb, void* param) {
	if (cur == NULL) return;

	splay_traverse(cur->left, cb, param);
	splay_traverse(cur->right, cb, param);
	cb(cur, param);
}

static inline void osplay_detach_sentinel(struct osplay* osplay) {
	if (osplay->root != NULL)
		osplay->root->parent = NULL;

	osplay->sentinel.left = NULL;
}

/* we have to re-associate the sentinel and the root node after we change the tree */
static inline void osplay_attach_sentinel(struct osplay* osplay) {
	osplay->sentinel.left = osplay->root;

	if (osplay->root != NULL)
		osplay->root->parent = &osplay->sentinel;
}

static void splaylink_dispose(struct splay_link* link, void* param) {
	struct osplay_node* node = container_of(link, struct osplay_node, link);
	struct osplay* osplay = (struct osplay*)param;

	/* delete the node it self */
	allocator_dealloc(osplay->allocator, node);
}
void splayset_clear(object o) {
	struct osplay* osplay = (struct osplay*)o;

	splay_traverse(osplay->root, splaylink_dispose, (void*)osplay);

	osplay->root = NULL;
	osplay_attach_sentinel(osplay);
	osplay->size = 0;
}

struct splaynode_clear_v {
	pf_ref_dispose_v callback;
	void*            context;
	struct osplay*   container;
};
static void splaylink_dispose_v(struct splay_link* link, void* param) {
	struct osplay_node* node = container_of(link, struct osplay_node, link);
	struct splaynode_clear_v* dp = (struct splaynode_clear_v*)param;

	/* first dispose the reference */
	if (dp->callback) {
		dp->callback((void*)node->reference, dp->context);
	}

	/* delete the node it self */
	/* delete the node it self */
	dbg_assert(dp && dp->container && dp->container->allocator);
	allocator_dealloc(dp->container->allocator, node);
}
void splayset_clear_v(object o, pf_ref_dispose_v dispose, void* context) {
	struct osplay* osplay = (struct osplay*)o;
	struct splaynode_clear_v dispose_context = {
		dispose, context, osplay
	};

	splay_traverse(osplay->root, splaylink_dispose_v, (void*)&dispose_context);

	osplay->root = NULL;
	osplay_attach_sentinel(osplay);
	osplay->size = 0;
}

int splayset_size(const_object o) {
	struct osplay* osplay = (struct osplay*)o;

	return osplay->size;
}

bool splayset_empty(const_object o) {
	struct osplay* osplay = (struct osplay*)o;
	return osplay->size == 0;
}

/* initialize all part of an iterator except the __current position */
static void osplay_itr_com_init(struct osplay_itr* itr, struct osplay* list) {
	itr->__offset = itr;
	itr->__cast   = osplay_itr_cast;

	itr->__iftable[0].__offset = (address)0;
	itr->__iftable[0].__vtable = (unknown)&__itr_vtable;

	itr->allocator = list->allocator;
	/* itr->__current = NULL; */
}

const_iterator splayset_itr_begin(const_object o) {
	struct osplay* osplay = (struct osplay*)o;

	osplay->itr_begin.current = splay_min(osplay->root);

	return (iterator)&osplay->itr_begin;
}

const_iterator splayset_itr_end(const_object o) {
	struct osplay* osplay = (struct osplay*)o;

	osplay->itr_end.current = &osplay->sentinel;

	return (iterator)&osplay->itr_end;
}

iterator splayset_itr_create(const_object o, itr_pos pos) {
	struct osplay* osplay = (struct osplay*)o;
	struct osplay_itr* n_itr = (struct osplay_itr*)
		allocator_alloc(osplay->allocator, sizeof(struct osplay_itr));

	osplay_itr_com_init(n_itr, osplay);

	if (pos == itr_begin) {
		if (osplay->root == NULL) {
			n_itr->current = &osplay->sentinel;
		} else {
			n_itr->current = splay_min(osplay->root);
		}
	}
	else {
		n_itr->current = &osplay->sentinel;
	}
	
	return (object)n_itr;
}

void splayset_itr_assign(const_object o, iterator itr, itr_pos pos) {
	struct osplay* osplay = (struct osplay*)o;
	struct osplay_itr* n_itr = (struct osplay_itr*)itr;

	osplay_itr_com_init(n_itr, osplay);

	if (pos == itr_begin) {
		if (osplay->root == NULL) {
			n_itr->current = &osplay->sentinel;
		} else {
			n_itr->current = splay_min(osplay->root);
		}
	}
	else {
		/* __sentinel will be the maximum element in the tree */
		n_itr->current = &osplay->sentinel;
	}
}

struct direct_s {
	pf_ref_compare  comp;
	pf_ref_compare_v compv;
	void*           cp_context;
	const void* target;
	const struct splay_link* candidate; /* only useful for multiple instances */
};

static int osplay_direct(const struct splay_link* link, void* param) {
	struct osplay_node* node = container_of(link, struct osplay_node, link);
	struct direct_s* dir    = (struct direct_s*)param;
	int    compr            = 0;

	if (dir->comp != NULL) {
		compr = dir->comp(node->reference, dir->target);
	} else {
		compr = dir->compv(node->reference, dir->target, dir->cp_context);
	}

	if (compr == 0)
		return 0;
	else if (compr < 0) /* we should expose right side */
		return 1;
	else 
		return -1;
}

static int osplay_direct_lower(const struct splay_link* link, void* param) {
	struct osplay_node* node = container_of(link, struct osplay_node, link);
	struct direct_s* dir    = (struct direct_s*)param;
	int    compr            = 0;

	if (dir->comp != NULL) {
		compr = dir->comp(node->reference, dir->target);
	} else {
		compr = dir->compv(node->reference, dir->target, dir->cp_context);
	}

	if (compr == 0) {
		dir->candidate = link; /* update the candidate */
		return -1; /* explore the left side */
	}
	else if (compr < 0) /* we should explore right side */
		return 1;
	else {
		dir->candidate = link;
		return -1;
	}

	/* never been here */
	return 0;
}

static int osplay_direct_upper(const struct splay_link* link, void* param) {
	struct osplay_node* node = container_of(link, struct osplay_node, link);
	struct direct_s* dir    = (struct direct_s*)param;
	int    compr            = 0;

	if (dir->comp != NULL) {
		compr = dir->comp(node->reference, dir->target);
	} else {
		compr = dir->compv(node->reference, dir->target, dir->cp_context);
	}

	if (compr == 0) {
		return 1; /* explore the right side */
	}
	else if (compr < 0) /* we should explore right side */
		return 1;
	else {
		dir->candidate = link; /* update the candidate */
		return -1;
	}

	/* never been here */
	return 0;
}

void splayset_itr_find_s(const_object o, iterator itr, const void* __ref) {
	struct osplay* osplay    = (struct osplay*)o;
	struct osplay_itr* oitr  = (struct osplay_itr*)itr;
	struct direct_s   dir    = { osplay->ref_comp, NULL, NULL, __ref, NULL };
	struct splay_link* find_res = NULL; 
	
	osplay_detach_sentinel(osplay);
	find_res = splay_dynamic_search(&osplay->root, osplay_direct, &dir);
	osplay_attach_sentinel(osplay);

	dbg_assert(dir.candidate == NULL);

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[0].__offset == (address)0);
	dbg_assert(itr->__iftable[0].__vtable == (unknown)&__itr_vtable);

	if (find_res != NULL) {
		oitr->current = find_res;
	}
	else {
		oitr->current = &osplay->sentinel;
	}
}

void splayset_itr_find_lower_m(const_object o, iterator itr, const void* __ref) {
	struct osplay* osplay    = (struct osplay*)o;
	struct osplay_itr* oitr  = (struct osplay_itr*)itr;
	struct direct_s   dir    = { osplay->ref_comp, NULL, NULL, __ref, NULL };
	struct splay_link* link  = NULL;

	osplay_detach_sentinel(osplay);
	link = splay_dynamic_search(&osplay->root, osplay_direct_lower, &dir);
	osplay_attach_sentinel(osplay);

	dbg_assert(link == NULL); /* we will always direct down */
	/* TODO: remove const cast */
	link = (struct splay_link*)dir.candidate;    /* the last candidate, the most closed to leaf one, is what we want */

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[0].__offset == (address)0);
	dbg_assert(itr->__iftable[0].__vtable == (unknown)&__itr_vtable);

	if (link != NULL) {
		oitr->current = link;
	}
	else {
		oitr->current = &osplay->sentinel;
	}
}

void splayset_itr_find_upper_m(const_object o, iterator itr, const void* __ref) {
	struct osplay* osplay    = (struct osplay*)o;
	struct osplay_itr* oitr  = (struct osplay_itr*)itr;
	struct direct_s   dir    = { osplay->ref_comp, NULL, NULL, __ref, NULL };
	struct splay_link* link  = NULL;
	
	osplay_detach_sentinel(osplay);
	link = splay_dynamic_search(&osplay->root, osplay_direct_upper, &dir);
	osplay_attach_sentinel(osplay);

	dbg_assert(link == NULL); /* we will always direct down */
	link = (struct splay_link*)dir.candidate;

	/* make sure the iterator type is right */
	dbg_assert(itr->__iftable[0].__offset == (address)0);
	dbg_assert(itr->__iftable[0].__vtable == (unknown)&__itr_vtable);

	if (link != NULL) { 
		oitr->current = link;
	}
	else {
		oitr->current = &osplay->sentinel;
	}
}

void* splayset_insert_s(object o, const void* __ref) {
	struct osplay* osplay     = (struct osplay*)o;
	struct osplay_node* node = (struct osplay_node*)
		allocator_alloc(osplay->allocator, sizeof(struct osplay_node));
	struct splay_link* duplicated = NULL;

	node->reference = __ref;
	osplay_detach_sentinel(osplay);
	if (osplay->ref_comp != NULL) {
		osplay->root = splay_insert_sv(osplay->root, &node->link, osplay_compare_c, osplay->ref_comp, &duplicated);
	} else {
		struct comp_pack cp_pack = { osplay->ref_comp_v, osplay->comp_context };
		osplay->root = splay_insert_sv(osplay->root, &node->link, osplay_compare_v, &cp_pack, &duplicated);
	}
	
	osplay_attach_sentinel(osplay);

	if (duplicated != NULL) {
		struct osplay_node* dup_node = container_of(duplicated, struct osplay_node, link);
		const void* old_ref = dup_node->reference;
		if (osplay->ref_comp != NULL) {
			dbg_assert(osplay_compare_c(&node->link, duplicated, osplay->ref_comp) == 0);
		} else {
			struct comp_pack cp_pack = { osplay->ref_comp_v, osplay->comp_context };
			dbg_assert(osplay_compare_v(&node->link, duplicated, &cp_pack) == 0);
		}
		
		allocator_dealloc(osplay->allocator, node);

		/* update the reference */
		dup_node->reference = __ref;
		return (void*)old_ref;
	}
	
	osplay->size ++;

	return NULL;
}

void splayset_insert_m(object o, const void* __ref) {
	struct osplay* osplay     = (struct osplay*)o;
	struct osplay_node* node = (struct osplay_node*)
		allocator_alloc(osplay->allocator, sizeof(struct osplay_node));

	node->reference = __ref;
	osplay_detach_sentinel(osplay);
	osplay->root = splay_insert_v(osplay->root, &node->link, osplay_compare_c, osplay->ref_comp);
	osplay_attach_sentinel(osplay);

	osplay->size ++;
	return;
}

bool splayset_contains(const_object o, const void* __ref) {
	struct osplay* osplay   = (struct osplay*)o;
	struct direct_s   dir   = { osplay->ref_comp, NULL, NULL, __ref, NULL };
	struct splay_link* link = NULL;
	
	osplay_detach_sentinel(osplay);
	link = splay_dynamic_search(&osplay->root, osplay_direct, &dir);
	osplay_attach_sentinel(osplay);

	if (link != NULL) {
		return true;
	}
	
	return false;
}

int splayset_count_m(const_object o, const void* __ref) {
	struct osplay*     osplay   = (struct osplay*)o;
	struct direct_s   dir       = { osplay->ref_comp, NULL, NULL, __ref, NULL };
	const struct splay_link* lb = NULL;
	
	osplay_detach_sentinel(osplay);
	lb = splay_dynamic_search(&osplay->root, osplay_direct_lower, &dir);
	dbg_assert(lb == NULL);
	osplay_attach_sentinel(osplay);

	lb = (dir.candidate);
	dir.candidate = NULL;
	if (lb != NULL) {
		const struct splay_link* ub = splay_search(osplay->root, osplay_direct_upper, &dir);
		int count = 0;

		dbg_assert(ub == NULL);
		ub = (dir.candidate);
		
		if (ub == NULL) 
			ub = &osplay->sentinel;

		while (lb != ub) {
			count ++;
			lb = splay_successor(lb, false);
		}

		return count;
	}

	return 0;
}

bool splayset_remove(object o, void* __ref) {
	struct osplay* osplay   = (struct osplay*)o;
	struct direct_s   dir   = { osplay->ref_comp, NULL, NULL, __ref, NULL };
	struct splay_link* link = NULL;
	
	osplay_detach_sentinel(osplay);
	link = splay_dynamic_search(&osplay->root, osplay_direct, &dir);
	osplay_attach_sentinel(osplay);

	if (link != NULL) {
		struct osplay_node* node = container_of(link, struct osplay_node, link);

		osplay_detach_sentinel(osplay);
		//osplay->root = splay_remove_v(osplay->root, link, osplay_compare_c, osplay->ref_comp);
		if (osplay->ref_comp != NULL) {
			osplay->root = splay_remove_v(osplay->root, link, osplay_compare_c, osplay->ref_comp);
		} else {
			struct comp_pack cp_pack = { osplay->ref_comp_v, osplay->comp_context };
			osplay->root = splay_remove_v(osplay->root, link, osplay_compare_v, &cp_pack);
		}
		osplay_attach_sentinel(osplay);

		allocator_dealloc(osplay->allocator, node);

		osplay->size --;

		return true;
	}

	return false;
}

void* splayset_itr_remove(object o, iterator itr) {
	struct osplay* osplay    = (struct osplay*)o;
	struct osplay_itr* oitr  = (struct osplay_itr*)itr;
	struct osplay_node* node = container_of(oitr->current, struct osplay_node, link);
	const void* obj_ref      = node->reference;

	dbg_assert(oitr->__cast == osplay_itr_cast);
	dbg_assert(oitr->current != NULL);

	osplay_detach_sentinel(osplay);
	//  osplay->root = splay_remove_v(osplay->root, &node->link, osplay_compare_c, osplay->ref_comp);
	if (osplay->ref_comp != NULL) {
		osplay->root = splay_remove_v(osplay->root, &node->link, osplay_compare_c, osplay->ref_comp);
	} else {
		struct comp_pack cp_pack = { osplay->ref_comp_v, osplay->comp_context };
		osplay->root = splay_remove_v(osplay->root, &node->link, osplay_compare_v, &cp_pack);
	}
	osplay_attach_sentinel(osplay);

	/* we only free the node pointer, not the reference, the reference is returned to the client */
	allocator_dealloc(osplay->allocator, node);

	osplay->size --;

	return (void*)obj_ref;
}

