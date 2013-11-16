#ifndef _OO_MODEL_H_
#define _OO_MODEL_H_

#include <cominc.h>
/*
 * For more detail about the oo model, please see oo_model.doc.h
 */
typedef void*        unknown;
typedef const void*  const_unknown;
typedef void*        address;
typedef unsigned int unique_id;
typedef unsigned int hashcode;

typedef unknown (*pf_cast)(unknown obj, unique_id type_id);

struct base_interface {
	/* for interface, __offset is the offset of the interface from the object which implements it 
	 * for example, the first interface's offset is 0, the second is 1. */
	address                   __offset;

	unknown                   __vtable;

};
typedef struct base_interface *_interface;
typedef const struct base_interface *const_interface;

struct base_object {
	/* for object, address is the abstract address the object */
	address                   __offset;

	/* NOTE: this function could be in the virtual function table, but that will cause duplication */
	pf_cast                   __cast;

	/* the object should know how many interfaces it has */
	struct base_interface     __iftable[1];

	/* the object running context */
	//allocator               __allocator;

	/* object specific members, i.e. */
	/*
	int x;
	struct someobject y;
	*/
};
typedef struct base_object *object;
typedef const struct base_object *const_object;

#define __MAX_NUM_INTERFACE_PER_OBJECT 10
/* 
 * get the object from a given interface
 */
extern inline object __object_from_interface(const_interface inf);

/*
 * test if an unknown address is an object.
 * currently, this test is a little weak, since the only rule we base is that:
 * for any object, the first (void*) bytes saves the address itself.
 */
extern inline bool __is_object(const_unknown x);

/*
 * test if an unknown address is an interface.
 * if unknown x is an interface, we could found the base object's address,
 * if the deduced 'object' is a real object, then this is a interface.
 */
extern inline bool __is_interface(const_unknown x);

/* 
 * cast everything,
 * from object to interface, from interface to object, 
 * from interface to interface(not common in c++), from object to object(which will return NULL since we 
 * have only one layer of inherit, that is object inherit from interfaces.
 */
extern inline unknown __cast(const_unknown x, unique_id id);

/* 
 * cast a object to one of its interfaces if you know the offset of the interface in the object.
 */
extern inline _interface __fast_cast(const_object x, int ifoffset);

/*
 * include the raw-pointer-object common processing functions.
 */
#include <oo_bridge.h>

#endif /* _OO_MODEL_H_ */
