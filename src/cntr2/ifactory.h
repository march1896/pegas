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

object* cntr_create_olist();
object* cntr_create_olist_v(allocator alc);

object* cntr_create_ollrb(pf_ref_compare comp);
/* if alc is NULL, create_v will create with multi-pool allocator to gain best efficiency */
object* cntr_create_ollrb_v(pf_ref_compare comp, allocator alc);

object* cntr_create_osplay(pf_ref_compare comp);
/* if alc is NULL, create_v will create with multi-pool allocator to gain best efficiency */
object* cntr_create_osplay_v(pf_ref_compare comp, allocator alc);

object* cntr_create_oskiplist(pf_ref_compare comp);
/* if alc is NULL, create_v will create with multi-pool allocator to gain best efficiency */
object* cntr_create_oskiplist_v(pf_ref_compare comp, allocator alc);

object* cntr_create_ordmap(pf_ref_compare key_compare);
enum ordmap_driver {
	ordmap_by_llrb,
	ordmap_by_splay,
	ordmap_by_skiplist,
	ordmap_driver_count
};
object* cntr_create_ordmap_v(pf_ref_compare key_compare, allocator alc, enum ordmap_driver driver_type);

#endif /* _INTERFACE_FACTORY_H_ */
