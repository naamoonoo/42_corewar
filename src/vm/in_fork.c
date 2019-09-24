/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:24:57 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/27 15:18:37 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

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
	child->pid = vm->next_available_pid;
	vm->next_available_pid++;
	process_prepare_instruction(child, gv);
	child->next = vm->p_list;
	vm->p_list = child;
}
