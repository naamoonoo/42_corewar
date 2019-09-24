/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:10 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/03 23:04:43 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void		in_lfork(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_process	*child;
	int			offset;

	UNUSED(gv);
	child = (t_process *)malloc(sizeof(t_process));
	if (child == NULL)
		return ;
	ft_memcpy(child, process, sizeof(t_process));
	offset = mem_read_ind(process->pc->next);
	child->pc = mem_ptr_add(process->pc, offset % MEM_SIZE);
	process->pc = process->pc->next->next->next;
	child->pid = vm->next_available_pid;
	vm->next_available_pid++;
	process_prepare_instruction(child, gv);
	child->next = vm->p_list;
	vm->p_list = child;
}
