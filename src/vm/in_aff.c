/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:21:56 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/13 21:26:43 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_aff(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	char		output;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[15], process, 1);
	if (args == NULL)
		return ;
	output = ((arg_list_read(args, 0, gv, process) + 128) % 256) - 128;
	write(1, &output, 1);
	free(args);
}
