#include <check.h>

#include "../include/corewar.h"
#include "../include/op.h"
#include "../include/test.h"

START_TEST (test_in_st)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(IDX_MOD + 42);
	process = process_new(1, mem);

	// st r13 r8
	WRITE_TO_MEM(mem, ((char[4]) {0x03, 0x50, 0x0D, 0x08}), 4);
	process->registers[13] = 42;
	in_st(NULL, process, NULL);
	ck_assert_int_eq(process->registers[8], 42);
	ck_assert_int_eq(process->registers[13], 42);

	// st r7 1
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x03, 0x70, 0x07, 0x00, 0x01}), 5);
	process->registers[7] = 0x01234567;
	in_st(NULL, process, NULL);
	ck_assert_int_eq(mem->next->data, 0x01);
	ck_assert_int_eq(mem->next->next->data, 0x23);
	ck_assert_int_eq(mem->next->next->next->data, 0x45);
	ck_assert_int_eq(mem->next->next->next->next->data, 0x67);

	// st r4 -2
	process->pc = mem->next->next;
	WRITE_TO_MEM(mem, ((char[7]) {0, 0, 0x03, 0x70, 0x04, 0xFF, 0xFE}), 7);
	process->registers[4] = 0xFEDCBA98;
	in_st(NULL, process, NULL);
	ck_assert_int_eq(mem->data, (char) 0xFE);
	ck_assert_int_eq(mem->next->data, (char) 0xDC);
	ck_assert_int_eq(mem->next->next->data, (char) 0xBA);
	ck_assert_int_eq(mem->next->next->next->data, (char) 0x98);

	// st r7 IDX_MOD+1
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x03, 0x70, 0x07, 0, 0}), 5);
	mem_write_ind(mem->next->next->next, IDX_MOD + 1);
	process->registers[7] = 0x76543210;
	in_st(NULL, process, NULL);
	ck_assert_int_eq(mem->next->data, 0x76);
	ck_assert_int_eq(mem->next->next->data, 0x54);
	ck_assert_int_eq(mem->next->next->next->data, 0x32);
	ck_assert_int_eq(mem->next->next->next->next->data, 0x10);

	// st r4 -IDX_MOD-2
	process->pc = mem->next->next;
	WRITE_TO_MEM(mem, ((char[7]) {0, 0, 0x03, 0x70, 0x04, 0, 0}), 7);
	mem_write_ind(mem->next->next->next->next->next, 0 - IDX_MOD - 2);
	process->registers[4] = 0x89ABCDEF;
	in_st(NULL, process, NULL);
	ck_assert_int_eq(mem->data, (char) 0x89);
	ck_assert_int_eq(mem->next->data, (char) 0xAB);
	ck_assert_int_eq(mem->next->next->data, (char) 0xCD);
	ck_assert_int_eq(mem->next->next->next->data, (char) 0xEF);
}
END_TEST

TCase *in_st_tcase()
{
	TCase *tc;

	tc = tcase_create("in_st");
	tcase_add_test(tc, test_in_st);
	return tc;
}
