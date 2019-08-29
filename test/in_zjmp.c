#include <check.h>

#include "../include/corewar.h"

START_TEST (test_in_zjmp)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(IDX_MOD + 42);
	process = process_new(1, mem);

	// zjmp %1
	mem->data = 0x09;
	mem->next->data = 0x00;
	mem->next->next->data = 0x01;
	process->carry = FALSE;
	in_zjmp(NULL, process, NULL);
	ck_assert_ptr_eq(process->pc, mem->next->next->next);

	// zjmp %1
	mem->data = 0x09;
	mem->next->data = 0x00;
	mem->next->next->data = 0x01;
	process->carry = TRUE;
	process->pc = mem;
	in_zjmp(NULL, process, NULL);
	ck_assert_ptr_eq(process->pc, mem->next);

	// zjmp %-1
	mem->next->data = 0x09;
	mem->next->next->data = 0xFF;
	mem->next->next->next->data = 0xFF;
	in_zjmp(NULL, process, NULL);
	ck_assert_ptr_eq(process->pc, mem);

	// zjmp %IDX_MOD+1
	mem->data = 0x09;
	mem_write_ind(mem->next, IDX_MOD + 1);
	in_zjmp(NULL, process, NULL);
	ck_assert_ptr_eq(process->pc, mem->next);

	// zjmp %-IDX_MOD-1
	mem->next->data = 0x09;
	mem_write_ind(mem->next->next, 0 - IDX_MOD - 1);
	in_zjmp(NULL, process, NULL);
	ck_assert_ptr_eq(process->pc, mem);
}
END_TEST

TCase *in_zjmp_tcase()
{
	TCase *tc;

	tc = tcase_create("in_zjmp");
	tcase_add_test(tc, test_in_zjmp);
	return tc;
}
