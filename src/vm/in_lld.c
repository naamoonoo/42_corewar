/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:24 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/13 21:26:17 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_lld(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	int			value;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[12], process, 0);
	if (args == NULL)
		return ;
	value = arg_list_read(args, 0, gv, process);
	process->carry = (value == 0);
	arg_list_write(args, 1, value, gv, process);
	free(args);
}
