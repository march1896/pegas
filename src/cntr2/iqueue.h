#ifndef _INTERFACE_QUEUE_H_
#define _INTERFACE_QUEUE_H_

/* the interface functions which support, used by clients */
#include <cntr2/oo_model.h>
#include <cntr2/idef.h>

extern inline       void     iqueue_clear       (Object* obj);
extern inline       void     iqueue_foreach     (Object* obj, pf_ref_process_v process, void* context);
extern inline       int      iqueue_size        (const Object* obj);
extern inline       bool     iqueue_empty       (const Object* obj);
extern inline const unknown* iqueue_front       (const Object* obj);
extern inline const unknown* iqueue_back        (const Object* obj);
extern inline       void     iqueue_push        (Object* obj, const unknown* __ref);
extern inline       void     iqueue_pop         (Object* obj);
extern inline       iterator iqueue_itr_create  (const Object* obj, itr_pos pos);
extern inline       void     iqueue_itr_assign  (const Object* obj, iterator itr, itr_pos pos);
extern inline const_iterator iqueue_itr_begin   (const Object* obj);
extern inline const_iterator iqueue_itr_end     (const Object* obj);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_iqueue_clear)       (Object* c);
typedef       void     (*pf_iqueue_foreach)     (Object* c, pf_ref_process_v process, void* context);
typedef       int      (*pf_iqueue_size)        (const Object* c);
typedef       bool     (*pf_iqueue_empty)       (const Object* c);
typedef const unknown* (*pf_iqueue_front)       (const Object* c);
typedef const unknown* (*pf_iqueue_back)        (const Object* c);
typedef       void     (*pf_iqueue_push)        (Object* c, const unknown* object);
typedef       void     (*pf_iqueue_pop)         (Object* c);
typedef       iterator (*pf_iqueue_itr_create)  (const Object* c, itr_pos pos);
typedef       void     (*pf_iqueue_itr_assign)  (const Object* c, iterator itr, itr_pos pos);
typedef const_iterator (*pf_iqueue_itr_begin)   (const Object* c);
typedef const_iterator (*pf_iqueue_itr_end)     (const Object* c);

struct iqueue_vtable {
	/* public */
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
