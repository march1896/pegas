#ifndef _INTERFACE_STACK_H_
#define _INTERFACE_STACK_H_

/* the interface functions which support, used by clients */
#include <oo_model.h>
#include <idef.h>

extern inline       void     istack_clear       (Object* obj);
extern inline       void     istack_foreach     (Object* obj, pf_ref_process_v process, void* context);
extern inline       int      istack_size        (const Object* obj);
extern inline       bool     istack_empty       (const Object* obj);
extern inline const unknown* istack_top         (const Object* obj);
extern inline       void     istack_push        (Object* obj, const unknown* __ref);
extern inline       void     istack_pop         (Object* obj);

extern inline       iterator istack_itr_create  (const Object* obj, itr_pos pos);
extern inline       void     istack_itr_assign  (const Object* obj, iterator itr, itr_pos pos);
extern inline const_iterator istack_itr_begin   (const Object* obj);
extern inline const_iterator istack_itr_end     (const Object* obj);

/* below is only useful for the container implementer */
/* the virtual functions that each container should implement */
typedef       void     (*pf_istack_clear)       (Object* c);
typedef       void     (*pf_istack_foreach)     (Object* c, pf_ref_process_v process, void* context);
typedef       int      (*pf_istack_size)        (const Object* c);
typedef       bool     (*pf_istack_empty)       (const Object* c);
typedef const unknown* (*pf_istack_top)         (const Object* c);
typedef       void     (*pf_istack_push)        (Object* c, const unknown* object);
typedef       void     (*pf_istack_pop)         (Object* c);

typedef       iterator (*pf_istack_itr_create)  (const Object* c, itr_pos pos);
typedef       void     (*pf_istack_itr_assign)  (const Object* c, iterator itr, itr_pos pos);
typedef const_iterator (*pf_istack_itr_begin)   (const Object* c);
typedef const_iterator (*pf_istack_itr_end)     (const Object* c);

struct istack_vtable {
	/* public */
	pf_istack_clear       __clear;
	pf_istack_foreach     __foreach;
	pf_istack_size        __size;
	pf_istack_empty       __empty;
	pf_istack_top         __top;
	pf_istack_push        __push;
	pf_istack_pop         __pop;

	pf_istack_itr_create  __itr_create;
	pf_istack_itr_assign  __itr_assign;
	pf_istack_itr_begin   __itr_begin;
	pf_istack_itr_end     __itr_end;
};

#endif /* _INTERFACE_STACK_H_ */
