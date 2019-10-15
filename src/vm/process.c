/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:36:58 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 14:42:02 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

t_process	*process_new(int pid, t_mem *pc)
{
	t_process	*process;
	int			i;

	process = malloc(sizeof(t_process));
	process->pid = pid;
	process->registers[1] = 0 - pid;
	process->carry = 0;
	i = 2;
	while (i <= REG_NUMBER)
	{
		process->registers[i] = 0;
		i++;
	}
	process->pc = pc;
	process->instruction = NULL;
	process->alive = FALSE;
	process->next = NULL;
	process->cycles_to_wait = 0;
	process->needs_to_be_prepared_on_the_next_cycle = FALSE;
	return (process);
}

t_instruction g_instructions[] =
{
	&in_live, &in_ld, &in_st, &in_add,
	&in_sub, &in_and, &in_or, &in_xor,
	&in_zjmp, &in_ldi, &in_sti, &in_fork,
	&in_lld, &in_lldi, &in_lfork, &in_aff,
	&in_lt, &in_gt, &in_aa
};

static void	in_do_nothing(t_vm *vm, t_process *process, t_visualizer *gv)
{
	UNUSED(vm);
	UNUSED(gv);
	process->pc = process->pc->next;
}

void		process_prepare_instruction(t_process *process, t_visualizer *gv)
{
	char		op_code;
	const t_op	*op;

	op_code = process->pc->data;
	if (op_code < 1 || op_code > MAX_OPS)
	{
		process->instruction = &in_do_nothing;
		process->cycles_to_wait = 1;
		return ;
	}
	process->instruction = g_instructions[op_code - 1];
	op = &g_op_tab[op_code - 1];
	process->cycles_to_wait = op->cycles;
	(*gv->instruction_read)(gv->data, process->pc);
}
