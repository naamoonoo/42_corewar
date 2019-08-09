#include <check.h>

#include "../include/corewar.h"

START_TEST (test_mem_block_create)
{
	t_mem *block;

	block = mem_block_create(0);
	ck_assert_ptr_null(block);

	block = mem_block_create(1);
	ck_assert_ptr_nonnull(block);
	ck_assert_ptr_eq(block, block->next);
	ck_assert_ptr_eq(block, block->prev);

	block = mem_block_create(2);
	ck_assert_ptr_nonnull(block);
	ck_assert_ptr_ne(block, block->next);
	ck_assert_ptr_eq(block->next, block->prev);

	block = mem_block_create(42);
	ck_assert_ptr_nonnull(block);
	t_mem *ptr1 = block;
	t_mem *ptr2 = block;
	for (int i = 0; i < 12; i++)
	{
		ptr1 = ptr1->next;
		ck_assert_ptr_nonnull(ptr1);
		ck_assert_ptr_ne(ptr1, block);
	}
	for (int i = 0; i < 30; i++)
	{
		ptr2 = ptr2->prev;
		ck_assert_ptr_nonnull(ptr2);
		ck_assert_ptr_ne(ptr2, block);
	}
	ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST (test_mem_block_free)
{
	t_mem *block;

	block = mem_block_create(1);
	mem_block_free(block);
	block = mem_block_create(42);
	mem_block_free(block);
	block = mem_block_create(500);
	mem_block_free(block);
	block = mem_block_create(10000);
	mem_block_free(block);
}
END_TEST

TCase *mem_block_tcase()
{
	TCase *tc;

	tc = tcase_create("mem_block");
	tcase_add_test(tc, test_mem_block_create);
	tcase_add_test(tc, test_mem_block_free);
	return tc;
}
