/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/16 19:31:02 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_st(t_vm *vm, t_process *process, t_visualizer *gv)
{
	t_arg_list	*args;
	int			value;

	UNUSED(vm);
	args = decode_arg_list(g_op_tab[2], process, 1);
	if (args == NULL)
		return ;
	value = arg_list_read(args, 0, gv, process);
	if (gv != NULL)
		gv->process = process;
	arg_list_write(args, 1, value, gv);
	free(args);
}
