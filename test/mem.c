#include <check.h>

#include "../include/corewar.h"

t_mem mem[] =
{
	/*  0 */ {0x00, mem + 22, mem + 1},
	/*  1 */ {0x00, mem + 0, mem + 2},
	/*  2 */ {0x00, mem + 1, mem + 3},
	/*  3 */ {0x00, mem + 2, mem + 4},
	/*  4 */ {0x01, mem + 3, mem + 5},
	/*  5 */ {0x00, mem + 4, mem + 6},
	/*  6 */ {0x00, mem + 5, mem + 7},
	/*  7 */ {0x00, mem + 6, mem + 8},
	/*  8 */ {0xFF, mem + 7, mem + 9},
	/*  9 */ {0xFF, mem + 8, mem + 10},
	/* 10 */ {0xFF, mem + 9, mem + 11},
	/* 11 */ {0x46, mem + 10, mem + 12},
	/* 12 */ {0xA6, mem + 11, mem + 13},
	/* 13 */ {0xEF, mem + 12, mem + 14},
	/* 14 */ {0x6F, mem + 13, mem + 15},
	/* 15 */ {0x31, mem + 14, mem + 16},
	/* 16 */ {0x69, mem + 15, mem + 17},
	/* 17 */ {0xA2, mem + 16, mem + 18},
	/* 18 */ {0x62, mem + 17, mem + 19},
	/* 19 */ {0x8B, mem + 18, mem + 20},
	/* 20 */ {0xFF, mem + 19, mem + 21},
	/* 21 */ {0x10, mem + 20, mem + 22},
	/* 22 */ {0x8D, mem + 21, mem + 0},
};

const short ind_values[] =
{
	0,
	0,
	0,
	1,
	256,
	0,
	0,
	255,
	-1,
	-1,
	-186,
	18086,
	-22801,
	-4241,
	28465,
	12649,
	27042,
	-23966,
	25227,
	-29697,
	-240,
	4237,
	-29440
};

const int dir_values[] =
{
	0,
	1,
	256,
	65536,
	16777216,
	255,
	65535,
	16777215,
	-186,
	-47450,
	-12146961,
	1185345391,
	-1494257871,
	-277925527,
	1865509282,
	829006434,
	1772249739,
	-1570599937,
	1653341968,
	-1946218355,
	-15692544,
	277676032,
	-1929379840
};

START_TEST (test_mem_read_ind)
{
	for (int i = 0; i < 23; i++)
		ck_assert_int_eq(ind_values[i], mem_read_ind(mem + i));
}
END_TEST

START_TEST (test_mem_read_dir)
{
	for (int i = 0; i < 23; i++)
		ck_assert_int_eq(dir_values[i], mem_read_dir(mem + i));
}
END_TEST

START_TEST (test_mem_write_dir)
{
	t_mem mem2[] =
	{
		/*  0 */ {0, mem2 + 3, mem2 + 1},
		/*  1 */ {0, mem2 + 0, mem2 + 2},
		/*  2 */ {0, mem2 + 1, mem2 + 3},
		/*  3 */ {0, mem2 + 2, mem2 + 0},
	};
	for (int i = 0; i < 23; i++)
	{
		mem_write_dir(mem2, dir_values[i]);
		const t_mem *ptr = mem + i;
		t_mem *ptr2 = mem2;
		for (int j = 0; j < 4; j++)
		{
			ck_assert_int_eq(ptr->data, ptr2->data);
			ptr = ptr->next;
			ptr2 = ptr2->next;
		}
	}
}
END_TEST

TCase *mem_tcase()
{
	TCase *tc;

	tc = tcase_create("mem");
	tcase_add_test(tc, test_mem_read_ind);
	tcase_add_test(tc, test_mem_read_dir);
	tcase_add_test(tc, test_mem_write_dir);
	return tc;
}
