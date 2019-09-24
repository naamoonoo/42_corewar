/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:04:38 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/16 22:04:01 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

int	read_arg_number(int argc, char **argv, int *i, t_vm *vm)
{
	int num;

	*i += 1;
	if (*i >= argc)
	{
		ft_fdprintf(2, "Error: %s must be followed by an argument.\n",
				argv[*i - 1]);
		free(vm);
		exit(1);
	}
	num = ft_atoi(argv[*i]);
	if (num == 0 && !ft_strequ(argv[*i], "0"))
	{
		ft_fdprintf(2, "Error: Invalid argument for %s: %s\n",
				argv[*i - 1], argv[*i]);
		free(vm);
		exit(1);
	}
	*i += 1;
	return (num);
}
