#include <check.h>

#include "../include/corewar.h"
#include "../include/op.h"

START_TEST (test_in_live)
{
	t_mem *mem;
	t_process *process1;
	t_process *process2;
	t_vm *vm;

	mem = mem_block_create(5);
	mem->data = 0x01;
	mem->next->data = 0xFF;
	mem->next->next->data = 0xFF;
	mem->next->next->next->data = 0xFF;
	mem->next->next->next->next->data = 0xFF;

	process1 = process_new(1, mem);
	process2 = process_new(2, NULL);
	process1->next = process2;

	vm = malloc(sizeof(t_vm));
	vm->p_list = process1;
	vm->num_champions = 2;
	vm->last_alive = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->delta = CYCLE_DELTA;

	vm->champions[0] = malloc(sizeof(t_champion));
	vm->champions[0]->number = 1;
	vm->champions[0]->name = "test";
	vm->champions[1] = malloc(sizeof(t_champion));
	vm->champions[1]->number = 2;
	vm->champions[1]->name = "test2";

	process1->alive = FALSE;
	process2->alive = FALSE;
	in_live(vm, process1);
	ck_assert(process1->alive);
	ck_assert(!process2->alive);
	ck_assert_int_eq(vm->last_alive, 1);

	mem->next->next->next->next->data = 0xFE;
	process1->alive = FALSE;
	process2->alive = FALSE;
	in_live(vm, process1);
	ck_assert(process1->alive);
	ck_assert(!process2->alive);
	ck_assert_int_eq(vm->last_alive, 2);

	mem->next->next->next->next->data = 0xFD;
	in_live(vm, process1);
	ck_assert_int_eq(vm->last_alive, 2);
}
END_TEST

TCase *in_live_tcase()
{
	TCase *tc;

	tc = tcase_create("in_live");
	tcase_add_test(tc, test_in_live);
	return tc;
}
