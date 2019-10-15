/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_gt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:25:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 14:06:04 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_gt(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[16], process, 1);
	if (args == NULL)
		return ;
	process->carry = arg_list_read(args, 0, gv, process)
					> arg_list_read(args, 1, gv, process);
	if (gv != NULL)
		gv->process = process;
	free(args);
}
