#include <ooworld/cls_buitintype.h>

#include <ooworld/ptc_basic.h>

void     (*ptc_basic_destroy) (Object* me);
Object*  (*ptc_basic_clone)   (const Object* me);
bool     (*ptc_basic_equals)  (const Object* me, const Object* other);
int      (*ptc_basic_compare) (const Object* me, const Object* other);
hashcode (*ptc_basic_hashcode)(const Object* me);

static struct basic_protocol cls_int_basic_ptc = {

};

static protocol* cls_int_get_protocol(unique_id ptc_id) {
	if (ptc_id == basic_ptc_id)
		return &cls_int_basic_ptc;

	return NULL;
}

static struct class_info cls_int_info = {
	"int",
	"class wrapper for builtin type int"
};

Class cls_int = {
	&cls_int_get_protocol,
	&cls_int_info
};
