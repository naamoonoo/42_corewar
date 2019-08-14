/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:34:12 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/12 13:36:00 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

int	valid_arg_list(t_op op, t_arg_list *args)
{
	int i;

	i = 0;
	while (i < op.param_num)
	{
		if (args->arg_types[i] == DIR_CODE)
		{
			if (!(op.arg_type[i] & T_DIR))
				return (FALSE);
		}
		else if (args->arg_types[i] == IND_CODE)
		{
			if (!(op.arg_type[i] & T_IND))
				return (FALSE);
		}
		else
		{
			if (!(op.arg_type[i] & T_REG))
				return (FALSE);
			if (args->args[i] == NULL)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
