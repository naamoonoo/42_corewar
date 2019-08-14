#include <check.h>

#include "../include/corewar.h"
#include "../include/op.h"
#include "../include/test.h"

START_TEST (test_in_ld)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(IDX_MOD + 42);
	process = process_new(1, mem);

	// ld %x01234567 r5
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x01, 0x23, 0x45, 0x67, 0x05}), 7);
	process->carry = TRUE;
	in_ld(NULL, process);
	ck_assert_int_eq(process->registers[5], 0x01234567);
	ck_assert_int_eq(process->carry, FALSE);

	// ld %0 r100
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 0x64}), 7);
	in_ld(NULL, process);
	ck_assert_int_eq(process->carry, FALSE);

	// ld %0 r-1
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 0xFF}), 7);
	in_ld(NULL, process);
	ck_assert_int_eq(process->carry, FALSE);

	// ld %0 r5
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 0x05}), 7);
	in_ld(NULL, process);
	ck_assert_int_eq(process->registers[5], 0x00000000);
	ck_assert_int_eq(process->carry, TRUE);

	// ld 5 r9 (xFEDCBA98)
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[9]) {0x02, 0xD0, 0x00, 0x05, 0x09, 0xFE, 0xDC, 0xBA, 0x98}), 9);
	in_ld(NULL, process);
	ck_assert_int_eq(process->registers[9], (int) 0xFEDCBA98);
	ck_assert_int_eq(process->carry, FALSE);

	// ld IDX_MOD+5 r9 (x89ABCDEF)
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[9]) {0x02, 0xD0, 0, 0, 0x09, 0x89, 0xAB, 0xCD, 0xEF}), 9);
	mem_write_ind(mem->next->next, IDX_MOD + 5);
	in_ld(NULL, process);
	ck_assert_int_eq(process->registers[9], (int) 0x89ABCDEF);
	ck_assert_int_eq(process->carry, FALSE);

	// (x0FD24B96) ld -4 r12
	process->pc = mem->next->next->next->next;
	WRITE_TO_MEM(mem, ((char[9]) {0x0F, 0xD2, 0x4B, 0x96, 0x02, 0xD0, 0xFF, 0xFC, 0x0C}), 9);
	in_ld(NULL, process);
	ck_assert_int_eq(process->registers[12], (int) 0x0FD24B96);
	ck_assert_int_eq(process->carry, FALSE);

	// (x69B42DF0) ld -IDX_MOD-4 r12
	process->pc = mem->next->next->next->next;
	WRITE_TO_MEM(mem, ((char[9]) {0x69, 0xB4, 0x2D, 0xF0, 0x02, 0xD0, 0, 0, 0x0C}), 9);
	mem_write_ind(mem->next->next->next->next->next->next, 0 - IDX_MOD - 4);
	in_ld(NULL, process);
	ck_assert_int_eq(process->registers[12], 0x69B42DF0);
	ck_assert_int_eq(process->carry, FALSE);
}
END_TEST

// https://stackoverflow.com/questions/1269568/how-to-pass-a-constant-array-literal-to-a-function-that-takes-a-pointer-without

TCase *in_ld_tcase()
{
	TCase *tc;

	tc = tcase_create("in_ld");
	tcase_add_test(tc, test_in_ld);
	return tc;
}
