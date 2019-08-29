/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:42 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/16 19:31:19 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_sub(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	int			diff;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[4], process, 1);
	if (args == NULL)
		return ;
	diff = arg_list_read(args, 0, gv, process)
		- arg_list_read(args, 1, gv, process);
	process->carry = (diff == 0);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 2, diff, gv);
	free(args);
}
