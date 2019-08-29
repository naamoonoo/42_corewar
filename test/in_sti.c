#include <check.h>

#include "../include/corewar.h"
#include "../include/test.h"

START_TEST (test_in_sti)
{
	t_mem *mem;
	t_process *process;

	mem = mem_block_create(IDX_MOD + 42);
	process = process_new(1, mem);

	// sti r3 r2 %1
	//         5 +1 =6
	WRITE_TO_MEM(mem, ((char[6]) {0x0B, 0x58, 0x03, 0x02, 0x00, 0x01}), 6);
	process->registers[2] = 5;
	process->registers[3] = 0x107EC6D1;
	in_sti(NULL, process, NULL);
	ck_assert_int_eq(mem_read_dir(mem->next->next->next->next->next->next, NULL, NULL), 0x107EC6D1);

	// sti r6 r4 r5
	//        42-37 =5
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0B, 0x54, 0x06, 0x04, 0x05}), 5);
	process->registers[4] = 42;
	process->registers[5] = -37;
	process->registers[6] = 0x63A30EE4;
	in_sti(NULL, process, NULL);
	ck_assert_int_eq(mem_read_dir(mem->next->next->next->next->next, NULL, NULL), 0x63A30EE4);

	// invalid register tests
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0B, 0x54, 0x06, 0xFF, 0x05}), 5);
	in_sti(NULL, process, NULL);

	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0B, 0x54, 0x06, 0x04, 0x64}), 5);
	in_sti(NULL, process, NULL);

	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0B, 0x54, 0xC0, 0x04, 0x05}), 5);
	in_sti(NULL, process, NULL);

	// IDX_MOD test
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[5]) {0x0B, 0x54, 0x06, 0x04, 0x05}), 5);
	process->registers[4] = IDX_MOD + 2;
	process->registers[5] = 2 * IDX_MOD + 3;
	process->registers[6] = 0x9751E05F;
	in_sti(NULL, process, NULL);
	ck_assert_int_eq(mem_read_dir(mem->next->next->next->next->next, NULL, NULL), (int) 0x9751E05F);

	// sti r7 %x01AD %xFE56
	//           429   -426 =3
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[7]) {0x0B, 0x68, 0x07, 0x01, 0xAD, 0xFE, 0x56}), 7);
	process->registers[7] = 0xBC455823;
	in_sti(NULL, process, NULL);
	ck_assert_int_eq(mem_read_dir(mem->next->next->next, NULL, NULL), (int) 0xBC455823);

	// sti r9 %3 r8
	//         3 +1 =4
	process->pc = mem;
	WRITE_TO_MEM(mem, ((char[6]) {0x0B, 0x64, 0x09, 0x00, 0x03, 0x08}), 6);
	process->registers[8] = 1;
	process->registers[9] = 0x7A4FB5ED;
	in_sti(NULL, process, NULL);
	ck_assert_int_eq(mem_read_dir(mem->next->next->next->next, NULL, NULL), 0x7A4FB5ED);

	// sti r10 7 %1
	//        -5 +1 =-4
	process->pc = mem->next->next->next->next;
	WRITE_TO_MEM(mem, ((char[15]) {0, 0, 0, 0, 0x0B, 0x78, 0x0A, 0x00, 0x07, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFB}), 15);
	process->registers[10] = 0xD967F460;
	in_sti(NULL, process, NULL);
	ck_assert_int_eq(mem_read_dir(mem, NULL, NULL), (int) 0xD967F460);

	// sti r12 -1 r11
	// -17527824 +17527820 = -4
	process->pc = mem->next->next->next->next;
	WRITE_TO_MEM(mem, ((char[10]) {0, 0, 0, 0x01, 0x0B, 0x74, 0x0C, 0xFF, 0xFF, 0x0B}), 10);
	process->registers[11] = -17527824;
	process->registers[12] = 0x50496B16;
	in_sti(NULL, process, NULL);
	ck_assert_int_eq(process->registers[12], 0x50496B16);
}
END_TEST

TCase *in_sti_tcase()
{
	TCase *tc;

	tc = tcase_create("in_sti");
	tcase_add_test(tc, test_in_sti);
	return tc;
}
