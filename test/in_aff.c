#include <check.h>

#include "../include/corewar.h"

START_TEST (test_in_aff)
{
	t_process *process;
	t_vm *vm;

	process = process_new(1, NULL);
	vm = malloc(sizeof(t_vm));
	vm->p_list = process;
	vm->last_alive = NULL;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->delta = CYCLE_DELTA;

	in_aff(vm, process, NULL);
}
END_TEST

TCase *in_aff_tcase()
{
	TCase *tc;

	tc = tcase_create("in_aff");
	tcase_add_test(tc, test_in_aff);
	return tc;
}
