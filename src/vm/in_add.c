/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:11:18 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/16 19:39:49 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void		in_add(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	int			sum;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[3], process, 1);
	if (args == NULL)
		return ;
	sum = arg_list_read(args, 0, gv, process)
		+ arg_list_read(args, 1, gv, process);
	process->carry = (sum == 0);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 2, sum, gv);
	free(args);
}
