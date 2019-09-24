/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:32 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/03 22:41:22 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_or(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	int			result;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[6], process, 1);
	if (args == NULL)
		return ;
	result = arg_list_read(args, 0, gv, process)
		| arg_list_read(args, 1, gv, process);
	process->carry = (result == 0);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 2, result, gv);
	free(args);
}
