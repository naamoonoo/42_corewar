#include <check.h>

#include "../include/corewar.h"
#include "../include/test.h"

START_TEST (test_in_and)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(IDX_MOD + 42);
	process = process_new(1, mem);

	// and r1 r2 r3
	WRITE_TO_MEM(mem, ((char[5]) {0x06, 0x54, 0x01, 0x02, 0x03}), 5);
	process->registers[1] = 0x01234567;
	process->registers[2] = 0x55555555;
	in_and(NULL, process);
	ck_assert_int_eq(process->registers[3], 0x01014545);
	ck_assert_int_eq(process->carry, FALSE);

	// and r1 r2 r3
	WRITE_TO_MEM(mem, ((char[5]) {0x06, 0x54, 0x01, 0x02, 0x03}), 5);
	process->registers[1] = 0x01234567;
	process->registers[2] = 0xFEDCBA98;
	in_and(NULL, process);
	ck_assert_int_eq(process->registers[3], 0x00000000);
	ck_assert_int_eq(process->carry, TRUE);

	// and r100 r2 r3
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x06, 0x54, 0x64, 0x02, 0x03}), 5);
	in_and(NULL, process);

	// and r1 r100 r3
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x06, 0x54, 0x01, 0x64, 0x03}), 5);
	in_and(NULL, process);

	// and r1 r2 r100
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x06, 0x54, 0x01, 0x02, 0x64}), 5);
	in_and(NULL, process);

	// and %xAAAAAAAA %x89ABCDEF r5
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[11]) {0x06, 0xA4, 0xAA, 0xAA, 0xAA, 0xAA, 0x89, 0xAB, 0xCD, 0xEF, 0x05}), 11);
	in_and(NULL, process);
	ck_assert_int_eq(process->registers[5], 0x88A888A8);
	ck_assert_int_eq(process->carry, FALSE);

	// and 7 11 r12
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[15]) {0x06, 0xF4, 0x00, 0x07, 0x00, 0x0B, 0x0C,
								   0x01, 0x23, 0x45, 0x67,
								   0x89, 0xAB, 0xCD, 0xEF}), 15);
	in_and(NULL, process);
	ck_assert_int_eq(process->registers[12], 0x01234567);
	ck_assert_int_eq(process->carry, FALSE);

	// and IDX_MOD IDX_MOD+4 r1
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x06, 0xF4, 0, 0, 0, 0, 0x01}), 7);
	mem_write_ind(mem->next->next, IDX_MOD);
	mem_write_ind(mem->next->next->next->next, IDX_MOD + 4);
	t_mem *ptr = mem_ptr_add(mem, IDX_MOD);
	mem_write_dir(ptr, 0xEF508C58);
	mem_write_dir(ptr->next->next->next->next, 0x783BF523);
	in_and(NULL, process);
	ck_assert_int_eq(process->registers[1], 0x68108400);
	ck_assert_int_eq(process->carry, FALSE);
}
END_TEST

TCase *in_and_tcase()
{
	TCase *tc;

	tc = tcase_create("in_and");
	tcase_add_test(tc, test_in_and);
	return tc;
}
