/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:24:57 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/13 20:11:17 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

static int	highest_pid(t_vm *vm)
{
	t_process	*p;
	int			max;

	max = 0;
	p = vm->p_list;
	while (p != NULL)
	{
		if (p->pid > max)
			max = p->pid;
		p = p->next;
	}
	return (max);
}

void		in_fork(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_process	*child;
	int			offset;

	UNUSED(gv);
	child = (t_process *)malloc(sizeof(t_process));
	if (child == NULL)
		return ;
	ft_memcpy(child, process, sizeof(t_process));
	offset = mem_read_ind(process->pc->next) % IDX_MOD;
	child->pc = mem_ptr_add(process->pc, offset);
	process->pc = process->pc->next->next->next;
	child->pid = highest_pid(vm) + 1;
	child->cycles_to_wait = 0;
	child->instruction = NULL;
	child->next = vm->p_list;
	vm->p_list = child;
}
