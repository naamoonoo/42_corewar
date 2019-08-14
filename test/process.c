#include <check.h>

#include "../include/corewar.h"

START_TEST (test_process_new)
{
	t_process *p;
	t_mem *mem;

	mem = malloc(sizeof(t_mem));

	p = process_new(1, mem);
	ck_assert_ptr_nonnull(p);
	ck_assert_int_eq(p->pid, 1);
	ck_assert_int_eq(p->registers[1], -1);
	for (int i = 2; i <= REG_NUMBER; i++)
		ck_assert_int_eq(p->registers[i], 0);
	ck_assert_int_eq(p->carry, FALSE);
	ck_assert_ptr_eq(p->pc, mem);
	ck_assert_int_eq(p->alive, FALSE);
	ck_assert_int_eq(p->cycles_to_wait, 0);

	p = process_new(2, mem);
	ck_assert_ptr_nonnull(p);
	ck_assert_int_eq(p->pid, 2);
	ck_assert_int_eq(p->registers[1], -2);

	p = process_new(42, mem);
	ck_assert_ptr_nonnull(p);
	ck_assert_int_eq(p->pid, 42);
	ck_assert_int_eq(p->registers[1], -42);
}
END_TEST

TCase *process_tcase()
{
	TCase *tc;

	tc = tcase_create("process");
	tcase_add_test(tc, test_process_new);
	return tc;
}
