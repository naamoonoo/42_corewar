#include <check.h>
#include <limits.h>

#include "../include/corewar.h"

START_TEST (test_in_add)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(4);
	mem->data = 0x04;
	mem->next->data = 0x01;
	mem->next->next->data = 0x02;
	mem->next->next->next->data = 0x03;
	process = process_new(1, mem);

	process->registers[1] = 1;
	process->registers[2] = 1;
	in_add(NULL, process);
	ck_assert_int_eq(process->registers[3], 2);
	ck_assert_int_eq(process->carry, FALSE);

	process->registers[1] = -1;
	process->registers[2] = -1;
	in_add(NULL, process);
	ck_assert_int_eq(process->registers[3], -2);
	ck_assert_int_eq(process->carry, FALSE);

	process->registers[1] = -1;
	process->registers[2] = 1;
	in_add(NULL, process);
	ck_assert_int_eq(process->registers[3], 0);
	ck_assert_int_eq(process->carry, TRUE);

	mem->next->data = 0x07;
	mem->next->next->data = 0x07;
	mem->next->next->next->data = 0x07;
	process->registers[7] = INT_MAX;
	in_add(NULL, process);
	ck_assert_int_eq(process->registers[7], -2);
	ck_assert_int_eq(process->carry, FALSE);

	mem->next->data = 0xFF;
	in_add(NULL, process);
	ck_assert_int_eq(process->registers[7], -2);
	ck_assert_int_eq(process->carry, FALSE);
}
END_TEST

TCase *in_add_tcase()
{
	TCase *tc;

	tc = tcase_create("in_add");
	tcase_add_test(tc, test_in_add);
	return tc;
}
