#ifndef _CNTR2_TEST_ELEMENTDATA_H_
#define _CNTR2_TEST_ELEMENTDATA_H_

#include "cntr2/oo_model.h"

/* module test data */
/*
 * you must define td_type and td_traits before you use the test data.
 *
 * #ifdef td_type int
 * #define td_traits int_traits
 * td_type* td_repo = td_int_repo;
 */

#define TD_NUM 100000
#define TD_STRING_MAX_LENGTH 30
extern address int_repo[TD_NUM];
extern address longint_repo[TD_NUM];
extern address float_repo[TD_NUM];
extern address double_repo[TD_NUM];
extern address char_repo[TD_NUM];
extern address string_repo[TD_NUM];

void td_repo_init();
void td_repo_deinit();

#endif /* _CNTR2_TEST_ELEMENTDATA_H_ */
