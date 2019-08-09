#include <check.h>
#include <stdlib.h>

#include "../include/corewar.h"

TCase *mem_tcase();
TCase *scheduler_tcase();
TCase *mem_block_tcase();
TCase *process_tcase();
TCase *in_live_tcase();
TCase *in_ld_tcase();
TCase *in_st_tcase();
TCase *in_add_tcase();
TCase *in_sub_tcase();
TCase *in_and_tcase();
TCase *in_or_tcase();
TCase *in_xor_tcase();
TCase *in_zjmp_tcase();
TCase *in_ldi_tcase();
//TCase *in_sti_tcase();
TCase *in_fork_tcase();
TCase *in_lld_tcase();
TCase *in_lldi_tcase();
TCase *in_lfork_tcase();
//TCase *in_aff_tcase();

int main()
{
	int no_failed = 0;
	Suite *s;
	SRunner *runner;

	s = suite_create("Suite");
	suite_add_tcase(s, mem_tcase());
	suite_add_tcase(s, mem_block_tcase());
	suite_add_tcase(s, process_tcase());
	suite_add_tcase(s, in_live_tcase());
	suite_add_tcase(s, in_ld_tcase());
	suite_add_tcase(s, in_st_tcase());
	suite_add_tcase(s, in_add_tcase());
	suite_add_tcase(s, in_sub_tcase());
	suite_add_tcase(s, in_and_tcase());
	suite_add_tcase(s, in_or_tcase());
	suite_add_tcase(s, in_xor_tcase());
	suite_add_tcase(s, in_zjmp_tcase());
	suite_add_tcase(s, in_ldi_tcase());
//	suite_add_tcase(s, in_sti_tcase());
	suite_add_tcase(s, in_fork_tcase());
	suite_add_tcase(s, in_lld_tcase());
	suite_add_tcase(s, in_lldi_tcase());
	suite_add_tcase(s, in_lfork_tcase());
//	suite_add_tcase(s, in_aff_tcase());
	suite_add_tcase(s, scheduler_tcase());
	runner = srunner_create(s);

	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
