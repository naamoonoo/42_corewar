/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:39 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/16 19:20:29 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_sti(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_mem		*ptr;
	t_arg_list	*args;
	int			offset;
	int			value;

	UNUSED(vm);
	ptr = process->pc;
	args = decode_arg_list(g_op_tab[10], process, 1);
	if (args == NULL)
		return ;
	value = arg_list_read(args, 0, gv, process);
	offset = arg_list_read(args, 1, gv, process)
		+ arg_list_read(args, 2, gv, process);
	offset %= IDX_MOD;
	ptr = mem_ptr_add(ptr, offset);
	mem_write_dir(ptr, value, gv, process);
	free(args);
}
