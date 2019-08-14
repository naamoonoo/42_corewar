#include <check.h>

#include "../include/corewar.h"
#include "../include/op.h"
#include "../include/test.h"

START_TEST (test_decode_arg_list)
{
	t_mem *mem;
	t_process *process;
	t_arg_list *args;

	mem = mem_block_create(42);
	process = process_new(1, mem);

	WRITE_TO_MEM(mem, ((char[5]) {0x02, 0xD0, 0x00, 0x02, 0x0D}), 5);
	args = decode_arg_list(g_op_tab[1], process, TRUE);
	ck_assert_ptr_nonnull(args);
	ck_assert_int_eq(args->arg_types[0], IND_CODE);
	ck_assert_int_eq(args->arg_types[1], REG_CODE);
	ck_assert_ptr_eq(args->args[0], mem->next->next);
	ck_assert_ptr_eq(args->args[1], &(process->registers[13]));
	ck_assert_ptr_eq(process->pc, mem->next->next->next->next->next);

	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x34, 0x56, 0x78, 0x9A, 0x07}), 7);
	args = decode_arg_list(g_op_tab[1], process, TRUE);
	ck_assert_ptr_nonnull(args);
	ck_assert_int_eq(args->arg_types[0], DIR_CODE);
	ck_assert_int_eq(args->arg_types[1], REG_CODE);
	ck_assert_int_eq((int) args->args[0], 0x3456789A);
	ck_assert_ptr_eq(args->args[1], &(process->registers[7]));
	ck_assert_ptr_eq(process->pc, mem->next->next->next->next->next->next->next);

	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x50}), 2);
	args = decode_arg_list(g_op_tab[1], process, TRUE);
	ck_assert_ptr_null(args);
	ck_assert_ptr_eq(process->pc, mem->next->next->next->next);

	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0xFF}), 2);
	args = decode_arg_list(g_op_tab[1], process, TRUE);
	ck_assert_ptr_null(args);
	ck_assert_ptr_eq(process->pc, mem->next->next->next->next->next->next);
}
END_TEST

TCase *decode_arg_list_tcase()
{
	TCase *tc;

	tc = tcase_create("decode_arg_list");
	tcase_add_test(tc, test_decode_arg_list);
	return tc;
}
