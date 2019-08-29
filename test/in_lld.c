#include <check.h>

#include "../include/corewar.h"
#include "../include/op.h"
#include "../include/test.h"

START_TEST (test_in_lld)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(IDX_MOD + 42);
	process = process_new(1, mem);

	// lld %x01234567 r5
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x01, 0x23, 0x45, 0x67, 0x05}), 7);
	process->carry = TRUE;
	in_lld(NULL, process, NULL);
	ck_assert_int_eq(process->registers[5], 0x01234567);
	ck_assert_int_eq(process->carry, FALSE);

	// lld %0 r100
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 0x64}), 7);
	in_lld(NULL, process, NULL);
	ck_assert_int_eq(process->carry, FALSE);

	// lld %0 r-1
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 0xFF}), 7);
	in_lld(NULL, process, NULL);
	ck_assert_int_eq(process->carry, FALSE);

	// lld %0 r5
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 0x05}), 7);
	in_lld(NULL, process, NULL);
	ck_assert_int_eq(process->registers[5], 0x00000000);
	ck_assert_int_eq(process->carry, TRUE);

	// lld 5 r9 (xFEDCBA98)
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[9]) {0x02, 0xD0, 0x00, 0x05, 0x09, 0xFE, 0xDC, 0xBA, 0x98}), 9);
	in_lld(NULL, process, NULL);
	ck_assert_int_eq(process->registers[9], (int) 0xFEDCBA98);
	ck_assert_int_eq(process->carry, FALSE);

	// lld IDX_MOD+5 r9 (x89ABCDEF)
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x02, 0xD0, 0, 0, 0x09}), 5);
	mem_write_ind(mem->next->next, IDX_MOD + 5);
	t_mem *ptr = mem_ptr_add(mem, IDX_MOD + 5);
	mem_write_dir(ptr, 0x89ABCDEF, NULL, NULL);
	in_lld(NULL, process, NULL);
	ck_assert_int_eq(process->registers[9], (int) 0x89ABCDEF);
	ck_assert_int_eq(process->carry, FALSE);

	// (x0FD24B96) lld -4 r12
	process->pc = mem->next->next->next->next;
	WRITE_TO_MEM(mem, ((char[9]) {0x0F, 0xD2, 0x4B, 0x96, 0x02, 0xD0, 0xFF, 0xFC, 0x0C}), 9);
	in_lld(NULL, process, NULL);
	ck_assert_int_eq(process->registers[12], 0x0FD24B96);
	ck_assert_int_eq(process->carry, FALSE);
}
END_TEST

// https://stackoverflow.com/questions/1269568/how-to-pass-a-constant-array-literal-to-a-function-that-takes-a-pointer-without

TCase *in_lld_tcase()
{
	TCase *tc;

	tc = tcase_create("in_lld");
	tcase_add_test(tc, test_in_lld);
	return tc;
}
