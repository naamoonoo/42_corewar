#include <check.h>

#include "../include/corewar.h"

START_TEST (test_in_lfork)
{
	t_mem *mem;
	t_process *parent;
	t_vm *vm;

	mem = mem_block_create(IDX_MOD + 42);
	mem->data = 0x0C;
	mem->next->data = 0x00;
	mem->next->next->data = 0x03;

	parent = process_new(1, mem);
	parent->pid = 1;
	parent->registers[1] = -1;
	parent->registers[7] = 42;
	parent->registers[REG_NUMBER] = 0x89ABCDEF;
	parent->carry = 1;
	parent->alive = TRUE;
	parent->next = NULL;
	parent->cycles_to_wait = 123;

	vm = malloc(sizeof(t_vm));
	vm->p_list = parent;

	in_lfork(vm, parent);
	// TODO Is the child process pushed to the front or the back of the list?
	ck_assert_ptr_nonnull(parent->next);
	t_process *child = parent->next;
	ck_assert_int_ne(child->pid, 1);
	ck_assert_int_eq(child->registers[1], -1);
	ck_assert_int_eq(child->registers[7], 42);
	ck_assert_int_eq(child->registers[REG_NUMBER], 0x89ABCDEF);
	ck_assert_int_eq(child->carry, 1);
	ck_assert_ptr_eq(child->pc, mem->next->next->next);
	ck_assert_int_eq(child->alive, TRUE);
	ck_assert_ptr_eq(child->next, NULL);
	ck_assert_int_eq(child->cycles_to_wait, 0);

	mem->next->data = 0x0C;
	mem->next->next->data = 0xFF;
	mem->next->next->next->data = 0xFF;
	child->pc = mem->next;
	in_lfork(vm, child);
	ck_assert_ptr_eq(parent->next, child);
	ck_assert_ptr_nonnull(child->next);
	t_process *grandchild = child->next;
	ck_assert_int_ne(grandchild->pid, 1);
	ck_assert_int_ne(grandchild->pid, child->pid);
	ck_assert_ptr_eq(grandchild->pc, mem);

	mem_write_ind(mem->next, IDX_MOD);
	in_lfork(vm, parent);
	ck_assert_ptr_eq(parent->next, child);
	ck_assert_ptr_eq(child->next, grandchild);
	ck_assert_ptr_nonnull(grandchild->next);
	t_process *child2 = grandchild->next;
	ck_assert_int_ne(child2->pid, 1);
	ck_assert_int_ne(child2->pid, child->pid);
	ck_assert_int_ne(child2->pid, grandchild->pid);
	ck_assert_ptr_eq(child2->pc, mem_ptr_add(mem, IDX_MOD));
}
END_TEST

TCase *in_lfork_tcase()
{
	TCase *tc;

	tc = tcase_create("in_lfork");
	tcase_add_test(tc, test_in_lfork);
	return tc;
}
