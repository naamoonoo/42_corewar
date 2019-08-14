#include <check.h>

#include "../include/corewar.h"

int		g_process_calls[10];

void	debug_instruction(t_vm *vm, t_process *process)
{
	process->instruction = &debug_instruction;
	process->cycles_to_wait = 50;
	vm->last_alive = process->pid;
	process->alive = 1;
	g_process_calls[process->pid]++;
}

START_TEST (test_purge_list)
{
	t_process *p1 = malloc(sizeof(t_process));
	t_process *p2 = malloc(sizeof(t_process));
	t_process *p3 = malloc(sizeof(t_process));
	t_process *p4 = malloc(sizeof(t_process));
	t_process *p5 = malloc(sizeof(t_process));
	t_process *p6 = malloc(sizeof(t_process));
	t_process *p7 = malloc(sizeof(t_process));
	p1->pid = 1;
	p2->pid = 2;
	p3->pid = 3;
	p4->pid = 4;
	p5->pid = 5;
	p6->pid = 6;
	p7->pid = 7;
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p4->next = p5;
	p5->next = p6;
	p6->next = p7;
	p7->next = NULL;
	p1->alive = 0;
	p2->alive = 1;
	p3->alive = 1;
	p4->alive = 0;
	p5->alive = 0;
	p6->alive = 1;
	p7->alive = 0;

	t_process *list = p1;
	purge_list(&list);
	char list_str[10] = "\0\0\0\0\0\0\0\0\0\0";
	t_process *iter = list;
	int i = 0;
	while (iter != NULL)
	{
		list_str[i] = '0' + iter->pid;
		iter = iter->next;
		i++;
	}
	ck_assert_str_eq(list_str, "236");
	ck_assert_int_eq(p2->alive, 0);
	ck_assert_int_eq(p3->alive, 0);
	ck_assert_int_eq(p6->alive, 0);

	purge_list(&list);
	ck_assert_ptr_null(list);
}
END_TEST

START_TEST (scheduler_main_test)
{
	t_vm *vm;
	t_process	*p1;
	t_process	*p2;
	t_process	*p3;
	t_process	*p4;
	t_process	*p5;
	t_process	*p6;
	t_process	*p7;
	t_process	*p8;
	t_process	*p9;

	p1 = (t_process*)malloc(sizeof(t_process));
	p2 = (t_process*)malloc(sizeof(t_process));
	p3 = (t_process*)malloc(sizeof(t_process));
	p4 = (t_process*)malloc(sizeof(t_process));
	p5 = (t_process*)malloc(sizeof(t_process));
	p6 = (t_process*)malloc(sizeof(t_process));
	p7 = (t_process*)malloc(sizeof(t_process));
	p8 = (t_process*)malloc(sizeof(t_process));
	p9 = (t_process*)malloc(sizeof(t_process));
	p1->pid = 1;
	p2->pid = 2;
	p3->pid = 3;
	p4->pid = 4;
	p5->pid = 5;
	p6->pid = 6;
	p7->pid = 7;
	p8->pid = 8;
	p9->pid = 9;
	p9->next = NULL;
	p8->next = p9;
	p7->next = p8;
	p6->next = p7;
	p5->next = p6;
	p4->next = p5;
	p3->next = p4;
	p2->next = p3;
	p1->next = p2;
	p1->alive = 0;
	p2->alive = 0;
	p3->alive = 0;
	p4->alive = 0;
	p5->alive = 0;
	p6->alive = 0;
	p7->alive = 0;
	p8->alive = 0;
	p9->alive = 0;
	p1->instruction = &debug_instruction;
	p2->instruction = &debug_instruction;
	p3->instruction = &debug_instruction;
	p4->instruction = &debug_instruction;
	p5->instruction = &debug_instruction;
	p6->instruction = &debug_instruction;
	p7->instruction = &debug_instruction;
	p8->instruction = &debug_instruction;
	p9->instruction = &debug_instruction;
	p1->cycles_to_wait = 9023;
	p2->cycles_to_wait = 1912;
	p3->cycles_to_wait = 76;
	p4->cycles_to_wait = 24;
	p5->cycles_to_wait = 84;
	p6->cycles_to_wait = 73;
	p7->cycles_to_wait = 19;
	p8->cycles_to_wait = 87;
	p9->cycles_to_wait = 35;

	vm = (t_vm*)malloc(sizeof(t_vm));
	vm->cycles_to_die = 2000;
	vm->p_list = p1;
	vm->delta = 5;

	for (int i = 1; i < 10; i++)
		g_process_calls[i] = 0;

	int status = scheduler(vm);
	ck_assert_int_eq(status, 0);
	ck_assert_int_eq(vm->last_alive, 8);
	ck_assert_int_eq(g_process_calls[1], 0);
	ck_assert_int_eq(g_process_calls[2], 197);
	ck_assert_int_eq(g_process_calls[3], 234);
	ck_assert_int_eq(g_process_calls[4], 235);
	ck_assert_int_eq(g_process_calls[5], 234);
	ck_assert_int_eq(g_process_calls[6], 234);
	ck_assert_int_eq(g_process_calls[7], 235);
	ck_assert_int_eq(g_process_calls[8], 234);
	ck_assert_int_eq(g_process_calls[9], 235);
	ck_assert_int_eq(vm->delta, 2560);
	int i = 0;
	while (vm->p_list)
	{
		vm->p_list = vm->p_list->next;
		i++;
	}
	printf("%d\n", i);
}
END_TEST

TCase *scheduler_tcase()
{
	TCase *tc;

	tc = tcase_create("mem");
	tcase_add_test(tc, test_purge_list);
	tcase_add_test(tc, scheduler_main_test);
	return tc;
}
