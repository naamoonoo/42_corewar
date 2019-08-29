/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:24:39 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/16 19:30:24 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_ld(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	int			value;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[1], process, 1);
	if (args == NULL)
		return ;
	value = arg_list_read(args, 0, gv, process);
	process->carry = (value == 0);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 1, value, gv);
	free(args);
}
