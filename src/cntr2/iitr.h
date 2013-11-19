#ifndef _INTERFACE_ITR_H_
#define _INTERFACE_ITR_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>
#include <iobject.h>

enum iterator_position {
	itr_begin,
	itr_end,
	itr_pos_count
};

#define itr_destroy iobject_destroy
#define itr_clone   iobject_clone
#define itr_equals  iobject_equals

extern inline bool          itr_assign   (const_iterator itr, iterator dest);
/* itr_get_ref return the referenc to object managed by the container internally, it's not modifiable, modify it on your own risk */
extern inline const_unknown itr_get_ref  (const_iterator itr);
extern inline void          itr_set_ref  (iterator itr, const_unknown __ref);
extern inline void          itr_to_prev  (iterator itr);
extern inline void          itr_to_next  (iterator itr);
extern inline void          itr_advance  (iterator itr, int length);
extern inline int           itr_distance (const_iterator from, const_iterator to);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef bool          (*pf_itr_equals)   (const_iterator itr_a, const_iterator itr_b);
typedef const_unknown (*pf_itr_get_ref)  (const_iterator citr);
typedef void          (*pf_itr_set_ref)  (iterator citr, const_unknown object);
typedef void          (*pf_itr_to_prev)  (iterator citr);
typedef void          (*pf_itr_to_next)  (iterator citr);
typedef void*         (*pf_itr_advance)  (iterator citr, int length);
typedef int           (*pf_itr_distance) (const_iterator citr_from, const_iterator citr_to);

#define is_itrref(itr) (__cast(itr, ITR_REF_ID) != NULL)
#define is_itracc(itr) (__cast(itr, ITR_ACC_ID) != NULL)
#define is_itrfwd(itr) (__cast(itr, ITR_FWD_ID) != NULL)
#define is_itrbid(itr) (__cast(itr, ITR_BID_ID) != NULL)
#define is_itrrac(itr) (__cast(itr, ITR_RAC_ID) != NULL)

enum itr_implemetation_conversion {
	itr_interface_iobject = 0,
	itr_interface_iterator,
	itr_interface_count
};

/* extends itr_base_vtable */
struct itr_readable_vtable { 
	/* readable interface */
	pf_itr_get_ref          __get_ref;
};

/* extends itr_readable_vtable */
struct itr_accessible_vtable {
	/* readable interface */
	pf_itr_get_ref          __get_ref;

	/* accessible interface */
	pf_itr_set_ref          __set_ref;
};

/* extends itr_accessible_vtable */
struct itr_forward_vtable {
	/* readable interface */
	pf_itr_get_ref          __get_ref;

	/* accessible interface */
	pf_itr_set_ref          __set_ref;

	/* forward interface */
	pf_itr_to_next          __to_next;
};

/* extends itr_forward_vtable */
struct itr_bidirectional_vtable {
	/* readable interface */
	pf_itr_get_ref          __get_ref;

	/* accessible interface */
	pf_itr_set_ref          __set_ref;

	/* forward interface */
	pf_itr_to_next          __to_next;

	/* bidirectional interface */
	pf_itr_to_prev          __to_prev;
};

/* extends itr_bidirectional_vtable */
struct itr_randomaccessible_vtable {
	/* readable interface */
	pf_itr_get_ref          __get_ref;

	/* accessible interface */
	pf_itr_set_ref          __set_ref;

	/* forward interface */
	pf_itr_to_next          __to_next;

	/* bidirectional interface */
	pf_itr_to_prev          __to_prev;

	/* random accessible interface */
	pf_itr_advance          __advance;
	pf_itr_distance         __distance;
};

#endif /* _INTERFACE_ITR_H_ */
