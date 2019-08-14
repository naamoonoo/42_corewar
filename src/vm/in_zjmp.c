/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:50 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/13 20:10:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_zjmp(t_vm *vm, t_process *process, t_visualizer *gv)
{
	int offset;

	UNUSED(vm);
	UNUSED(gv);
	if (process->carry == 1)
		offset = mem_read_ind(process->pc->next) % IDX_MOD;
	else
		offset = 3;
	process->pc = mem_ptr_add(process->pc, offset);
}
