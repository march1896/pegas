#ifndef _INTERFACE_FACTORY_H_
#define _INTERFACE_FACTORY_H_

#include <oo_model.h>
#include <idef.h>

#define as_list(obj)  (iobject*)__cast((obj), ILIST_ID)
#define as_queue(obj) (iobject*)__cast((obj), IQUEUE_ID)
#define as_stack(obj) (iobject*)__cast((obj), ISTACK_ID)
#define as_set(obj)   (iobject*)__cast((obj), ISET_ID)
#define as_mset(obj)  (iobject*)__cast((obj), IMSET_ID)
#define as_map(obj)   (iobject*)__cast((obj), IMAP_ID)
#define as_mmap(obj)  (iobject*)__cast((obj), IMMAP_ID)

/* if create without allocator, it will use the global_default_allocator
 * if the alc == NULL, the create_a will create with a multi-poll allocator for best efficiency */


object* cntr_create_olist();
object* cntr_create_olist_a(allocator alc);

object* cntr_create_ollrb(pf_ref_compare comp);
object* cntr_create_ollrb_a(pf_ref_compare comp, allocator alc);
object* cntr_create_ollrb_v(pf_ref_compare_v comp_v, void* comp_context);
object* cntr_create_ollrb_va(pf_ref_compare_v comp_v, void* comp_context, allocator alc);

object* cntr_create_osplay(pf_ref_compare comp);
object* cntr_create_osplay_a(pf_ref_compare comp, allocator alc);
object* cntr_create_osplay_v(pf_ref_compare_v comp_v, void* comp_context);
object* cntr_create_osplay_va(pf_ref_compare_v comp_v, void* comp_context, allocator alc);

object* cntr_create_oskiplist(pf_ref_compare comp);
object* cntr_create_oskiplist_a(pf_ref_compare comp, allocator alc);
object* cntr_create_oskiplist_v(pf_ref_compare_v comp_v, void* comp_context);
object* cntr_create_oskiplist_va(pf_ref_compare_v comp_v, void* comp_context, allocator alc);

struct pair {
	const void* key;
	void*       value;
};

object* cntr_create_ordmap(pf_ref_compare key_compare);
enum ordmap_driver {
	ordmap_by_llrb,
	ordmap_by_splay,
	ordmap_by_skiplist,
	ordmap_driver_count
};
object* cntr_create_ordmap_v(pf_ref_compare key_compare, allocator alc, enum ordmap_driver driver_type);

#endif /* _INTERFACE_FACTORY_H_ */
