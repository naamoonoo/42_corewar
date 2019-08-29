#include <check.h>
#include <limits.h>

#include "../include/corewar.h"

START_TEST (test_in_sub)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(4);
	mem->data = 0x05;
	mem->next->data = 0x54;
	mem->next->next->data = 0x01;
	mem->next->next->next->data = 0x02;
	mem->next->next->next->next->data = 0x03;
	process = process_new(1, mem);

	process->registers[1] = 2;
	process->registers[2] = 1;
	in_sub(NULL, process, NULL);
	ck_assert_int_eq(process->registers[3], 1);
	ck_assert_int_eq(process->carry, FALSE);

	process->registers[1] = -2;
	process->registers[2] = -1;
	process->pc = mem;
	in_sub(NULL, process, NULL);
	ck_assert_int_eq(process->registers[3], -1);
	ck_assert_int_eq(process->carry, FALSE);

	mem->next->next->data = 0x07;
	mem->next->next->next->data = 0x07;
	mem->next->next->next->next->data = 0x07;
	process->registers[7] = INT_MAX;
	process->pc = mem;
	in_sub(NULL, process, NULL);
	ck_assert_int_eq(process->registers[7], 0);
	ck_assert_int_eq(process->carry, TRUE);

	mem->next->data = 0xFF;
	process->pc = mem;
	in_sub(NULL, process, NULL);
}
END_TEST

TCase *in_sub_tcase()
{
	TCase *tc;

	tc = tcase_create("in_sub");
	tcase_add_test(tc, test_in_sub);
	return tc;
}
