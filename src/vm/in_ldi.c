/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:24:44 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/27 15:19:23 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_ldi(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_mem		*ptr;
	t_arg_list	*args;
	int			offset;
	int			value;

	UNUSED(vm);
	ptr = process->pc;
	args = decode_arg_list(g_op_tab[9], process, 1);
	if (args == NULL)
		return ;
	offset = arg_list_read(args, 0, gv, process)
		+ arg_list_read(args, 1, gv, process);
	offset %= IDX_MOD;
	ptr = mem_ptr_add(ptr, offset);
	value = mem_read_dir(ptr, gv, process);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 2, value, gv);
	free(args);
}
