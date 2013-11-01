#ifndef _SKIP_LINK_H_
#define _SKIP_LINK_H_

#include <cominc.h>
#include <memheap/heap_def.h>

extern inline const struct skip_link* skip_link_next(const struct skip_link* cur);
extern inline const struct skip_link* skip_link_prev(const struct skip_link* cur);
extern inline const void*             skip_link_getref(const struct skip_link* slink);

typedef int (*pf_skiplist_compare)(const void* ref_a, const void* ref_b);

struct skiplist* skiplist_create(pf_skiplist_compare comp);
struct skiplist* skiplist_create_v(pf_skiplist_compare comp, pf_alloc alc, pf_dealloc dlc, void* heap);
void   skiplist_destroy(struct skiplist* list);

void skiplist_insert  (struct skiplist* list, const void* data);
void* skiplist_insert_s(struct skiplist* list, const void* data);
bool skiplist_contains(const struct skiplist* list, const void* data);
bool skiplist_remove  (struct skiplist* list, const void* data);
void skiplist_remove_link(struct skiplist* list, struct skip_link* link);
void skiplist_clear   (struct skiplist* list);
bool skiplist_empty   (const struct skiplist* list);

extern inline const struct skip_link* skiplist_first(const struct skiplist* list);
extern inline const struct skip_link* skiplist_last (const struct skiplist* list);
extern inline const struct skip_link* skiplist_sent (const struct skiplist* list);
const struct skip_link* skiplist_search(const struct skiplist* list, const void* data);
enum skiplist_search_option {
	skiplist_equal,
	skiplist_min_greater,
	skiplist_min_greaterorequal,
	skiplist_max_smaller,
	skiplist_max_smallerorequal,
	skiplist_search_count
};
/* the result may contains sentinel link */
const struct skip_link* skiplist_search_v(const struct skiplist* slist, const void* data, enum skiplist_search_option option);

#include <oo_ref.h>
/* note, if you change the inner value of ref, it may destroy the skiplist order */
void skiplist_foreach(struct skiplist* list, pf_ref_visit_v process, void* context);

#endif /* _SKIP_LINK_H_ */

