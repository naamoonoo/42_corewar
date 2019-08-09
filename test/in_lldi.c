#include <check.h>

#include "../include/corewar.h"
#include "../include/test.h"

START_TEST (test_in_lldi)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(IDX_MOD + 42);
	process = process_new(1, mem);

	// lldi r2 %1 r3
	//      5 +1 =6
	WRITE_TO_MEM(mem, ((char[10]) {0x0A, 0x64, 0x02, 0x00, 0x01, 0x03, 0x10, 0x7E, 0xC6, 0xD1}), 10);
	process->registers[2] = 5;
	process->carry = TRUE;
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[3], 0x107EC6D1);
	ck_assert_int_eq(process->carry, FALSE);

	// lldi r4 r5 r6
	//     42-37 =5
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[9]) {0x0A, 0x54, 0x04, 0x05, 0x06, 0x63, 0xA3, 0x0E, 0xE4}), 9);
	process->registers[4] = 42;
	process->registers[5] = -37;
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[6], 0x63A30EE4);
	ck_assert_int_eq(process->carry, FALSE);

	// carry test
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[9]) {0x0A, 0x54, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00}), 9);
	process->registers[4] = 42;
	process->registers[5] = -37;
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[6], 0x00000000);
	ck_assert_int_eq(process->carry, TRUE);

	// invalid register tests
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0A, 0x54, 0xFF, 0x05, 0x06}), 5);
	in_lldi(NULL, process);

	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0A, 0x54, 0x04, 0x64, 0x06}), 5);
	in_lldi(NULL, process);

	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0A, 0x54, 0x04, 0x05, 0xC0}), 5);
	in_lldi(NULL, process);

	// IDX_MOD test
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0A, 0x54, 0x04, 0x05, 0x06}), 5);
	process->registers[4] = IDX_MOD + 2;
	process->registers[5] = 3;
	t_mem *ptr = mem_ptr_add(mem, IDX_MOD + 5);
	mem_write_dir(ptr, 0x9751E05F);
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[6], 0x9751E05F);
	ck_assert_int_eq(process->carry, FALSE);

	// lldi %x01AD %xFE5A r7
	//        429   -422 =7
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[11]) {0x0A, 0xA4, 0x01, 0xAD, 0xFE, 0x5A, 0x07, 0xBC, 0x45, 0x58, 0x23}), 11);
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[7], 0xBC455823);
	ck_assert_int_eq(process->carry, FALSE);

	// lldi %3 r8 r9
	//      3 +3 =6
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[10]) {0x0A, 0x94, 0x00, 0x03, 0x08, 0x09, 0x7A, 0x4F, 0xB5, 0xED}), 10);
	process->registers[8] = 3;
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[9], 0x7A4FB5ED);
	ck_assert_int_eq(process->carry, FALSE);

	// lldi 7 %1 r10
	//    -5 +1 =-4
	process->pc = mem->next->next->next->next;
	WRITE_TO_MEM(mem, ((char[15]) {0xD9, 0x67, 0xF4, 0x60, 0x0A, 0xE4, 0x00, 0x07, 0x00, 0x01, 0x0A, 0xFF, 0xFF, 0xFF, 0xFB}), 15);
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[10], 0xD967F460);
	ck_assert_int_eq(process->carry, FALSE);

	// lldi -1 r11 r12
	// 369808639 -369808635 = -4
	process->pc = mem->next->next->next->next;
	WRITE_TO_MEM(mem, ((char[10]) {0x50, 0x49, 0x6B, 0x16, 0x0A, 0xD4, 0xFF, 0xFF, 0x0B, 0x0C}), 10);
	process->registers[11] = 369808635;
	in_lldi(NULL, process);
	ck_assert_int_eq(process->registers[12], 0x50496B16);
	ck_assert_int_eq(process->carry, FALSE);
}
END_TEST

TCase *in_lldi_tcase()
{
	TCase *tc;

	tc = tcase_create("in_lldi");
	tcase_add_test(tc, test_in_lldi);
	return tc;
}
