/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:20:02 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/16 19:41:22 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

/*
** n is assumed to be valid
*/

int			arg_list_read(t_arg_list *args, int n, t_visualizer *gv,
		t_process *p)
{
	t_mem	*mem;
	int		*reg;

	if (args->arg_types[n] == DIR_CODE)
		return ((int)args->args[n]);
	else if (args->arg_types[n] == IND_CODE)
	{
		mem = args->args[n];
		return (mem_read_dir(mem, gv, p));
	}
	else
	{
		reg = args->args[n];
		return (*reg);
	}
}

void		arg_list_write(t_arg_list *args, int n, int value, t_visualizer *gv)
{
	t_mem	*mem;
	int		*reg;

	if (args->arg_types[n] == IND_CODE)
	{
		mem = args->args[n];
		if (gv == NULL)
			mem_write_dir(mem, value, NULL, NULL);
		else
			mem_write_dir(mem, value, gv, gv->process);
	}
	else if (args->arg_types[n] == REG_CODE)
	{
		reg = args->args[n];
		*reg = value;
	}
}

void		arg_list_print(t_arg_list *args)
{
	int i;

	ft_printf("ArgList\n");
	i = 0;
	while (i < 3)
	{
		if (args->arg_types[i] == DIR_CODE)
			ft_printf("   DIR %.8X\n", (int)args->args[i]);
		else if (args->arg_types[i] == IND_CODE)
			ft_printf("   IND %p\n", args->args[i]);
		else
			ft_printf("   REG %p\n", args->args[i]);
		i++;
	}
}
