#include <block_link.h>
#include <list_link.h>

/**********************************************************************************/

struct list_link *blink_inc_find_ff (struct list_link* psent, int req) {
	struct list_link *itr = psent->next;
	while (itr != psent) {
		if (block_data_size_from_blick(itr) >= req) 
			return itr;

		itr = itr->next;
	}

	return NULL;
}

struct list_link *blink_inc_find_bf (struct list_link* psent, int req) {
	return blink_inc_find_ff(psent, req);
}

void   blink_inc_pop  (struct list_link* psent, struct list_link *pbd) {
	list_remove(psent, pbd);
}

void   blink_inc_push (struct list_link* psent, struct list_link *pbd) {
	if (list_empty(psent)) {
		list_insert_front(psent, pbd);
	}
	else {
		struct list_link* next = psent->next;
		struct list_link* prev = NULL;
		int sz = block_data_size_from_blick(pbd);

		while (next != psent) {
			if (block_data_size_from_blick(next) >= sz)
				break;

			prev = next;
			next = next->next;
		}

		list_link(pbd, prev, next);
	}

	return;
}

struct list_link *blink_rnd_find_ff (struct list_link* psent, int req) {
	return blink_inc_find_ff(psent, req);
}
struct list_link *blink_rnd_find_bf (struct list_link* psent, int req) {
	struct list_link *best = NULL;
	struct list_link *itr = psent->next;
	int bsz = -1;

	while (itr != psent) {
		int sz = block_data_size_from_blick(itr);

		if (sz >= req) {
			if (best == NULL || sz < bsz) {
				bsz = sz;
				best = itr;
			}
		}

		itr = itr->next;
	}

	return best;
}
void blink_rnd_pop  (struct list_link* psent, struct list_link *pbd) {
	list_remove(psent, pbd);
}
void blink_rnd_push (struct list_link* psent, struct list_link *pbd) {
	list_insert_front(psent, pbd);
}