#include <ialgo.h>
#include <iitr.h>
#include <ifactory.h>
#include <memheap/heap_global.h>

void foreach(const_iterator begin, const_iterator end, pf_ref_visit cb) {
	iterator itr = itr_clone(begin);

	dbg_assert(is_itrfwd(begin));
	dbg_assert(is_itrfwd(end));

	while (!itr_equals(itr, end)) {
		const_unknown __ref = itr_get_ref(itr);
		cb(__ref);
		itr_to_next(itr);
	}

	itr_destroy(itr);

	return;
}

void foreach_v(const_iterator begin, const_iterator end, pf_ref_visit_v cb, void* param) {
	iterator itr = itr_clone(begin);

	dbg_assert(is_itrfwd(begin));
	dbg_assert(is_itrfwd(end));

	while (!itr_equals(itr, end)) {
		const_unknown __ref = itr_get_ref(itr);
		cb(__ref, param);
		itr_to_next(itr);
	}

	itr_destroy(itr);
	return;
}

void sort_b(const_iterator begin, const_iterator end, pf_ref_compare comp) {
	dbg_assert(is_itrbid(begin));
	dbg_assert(is_itrbid(end));
}
void sort_r(const_iterator begin, const_iterator end, pf_ref_compare comp) {
	dbg_assert(is_itrrac(begin));
	dbg_assert(is_itrrac(end));
}

void reverse_b(const_iterator __begin, const_iterator __end) {
	iterator begin = itr_clone(__begin);
	iterator end   = itr_clone(__end);

	dbg_assert(is_itrbid(begin));
	dbg_assert(is_itrbid(end));

	if (itr_equals(begin, end)) {
		return;
	}

	itr_to_prev(end);
	while (!itr_equals(begin, end)) {
		itr_swap_ref(begin, end);

		itr_to_next(begin);

		if (itr_equals(begin, end)) {
			break;
		}
		
		itr_to_prev(end);
	}

	itr_destroy(begin);
	itr_destroy(end);

	return;
}

void prev_permutation_b(const_iterator begin, const_iterator end) {
	dbg_assert(is_itrbid(begin));
	dbg_assert(is_itrbid(end));
}

void next_permutation_b(const_iterator begin, const_iterator end) {
	dbg_assert(is_itrbid(begin));
	dbg_assert(is_itrbid(end));
}
