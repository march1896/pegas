#ifndef _INTERFACE_QUEUE_H_
#define _INTERFACE_QUEUE_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>

extern inline       void     iqueue_destroy     (object obj);
extern inline       void     iqueue_clear       (object obj);
extern inline       void     iqueue_foreach     (object obj, pf_ref_process_v process, void* context);
extern inline       int      iqueue_size        (const_object obj);
extern inline       bool     iqueue_empty       (const_object obj);
extern inline const_unknown  iqueue_front       (const_object obj);
extern inline const_unknown  iqueue_back        (const_object obj);
extern inline       void     iqueue_push        (object obj, const_unknown __ref);
extern inline       void     iqueue_pop         (object obj);
extern inline       iterator iqueue_itr_create  (const_object obj, itr_pos pos);
extern inline       void     iqueue_itr_assign  (const_object obj, iterator itr, itr_pos pos);
extern inline const_iterator iqueue_itr_begin   (const_object obj);
extern inline const_iterator iqueue_itr_end     (const_object obj);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_iqueue_destroy)     (object c);
typedef       void     (*pf_iqueue_clear)       (object c);
typedef       void     (*pf_iqueue_foreach)     (object c, pf_ref_process_v process, void* context);
typedef       int      (*pf_iqueue_size)        (const_object c);
typedef       bool     (*pf_iqueue_empty)       (const_object c);
typedef const_unknown  (*pf_iqueue_front)       (const_object c);
typedef const_unknown  (*pf_iqueue_back)        (const_object c);
typedef       void     (*pf_iqueue_push)        (object c, const_unknown object);
typedef       void     (*pf_iqueue_pop)         (object c);
typedef       iterator (*pf_iqueue_itr_create)  (const_object c, itr_pos pos);
typedef       void     (*pf_iqueue_itr_assign)  (const_object c, iterator itr, itr_pos pos);
typedef const_iterator (*pf_iqueue_itr_begin)   (const_object c);
typedef const_iterator (*pf_iqueue_itr_end)     (const_object c);

struct iqueue_vtable {
	/* public */
	pf_iqueue_destroy     __destroy;
	pf_iqueue_clear       __clear;
	pf_iqueue_foreach     __foreach;
	pf_iqueue_size        __size;
	pf_iqueue_empty       __empty;
	pf_iqueue_front       __front;
	pf_iqueue_back        __back;
	pf_iqueue_push        __push;
	pf_iqueue_pop         __pop;

	pf_iqueue_itr_create  __itr_create;
	pf_iqueue_itr_assign  __itr_assign;
	pf_iqueue_itr_begin   __itr_begin;
	pf_iqueue_itr_end     __itr_end;
};

#endif /* _INTERFACE_QUEUE_H_ */
