/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_aa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:31:06 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 14:18:07 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_aa(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	int			value;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[18], process, 1);
	if (args == NULL)
		return ;
	value = arg_list_read(args, 0, gv, process);
	process->carry = (value == 0);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 1, value, gv);
	arg_list_write(args, 2, value, gv);
	free(args);
}
