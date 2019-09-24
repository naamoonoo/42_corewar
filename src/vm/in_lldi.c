/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:29 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/03 23:08:53 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_lldi(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_mem		*ptr;
	t_arg_list	*args;
	int			offset;
	int			value;

	UNUSED(vm);
	ptr = process->pc;
	args = decode_arg_list(g_op_tab[13], process, 1);
	if (args == NULL)
		return ;
	offset = arg_list_read(args, 0, gv, process)
		+ arg_list_read(args, 1, gv, process);
	ptr = mem_ptr_add(ptr, offset);
	value = mem_read_dir(ptr, gv, process);
	process->carry = (value == 0);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 2, value, gv);
	free(args);
}
