/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:47:30 by aderby            #+#    #+#             */
/*   Updated: 2019/08/06 20:36:01 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/asm.h"

void	decode(int *fd, t_op op_tab)
{
	char	c;
	int		arg_type;
	int		i;

	i = 0;
	read(INPUT, &c, 1);
	while (i < op_tab.param_num)
	{
		arg_type = ((int)c >> (6 - 2 * i)) & 0b11;
		if (arg_type == DIR_CODE)
			parse_direct(fd, op_tab);
		else if (arg_type == IND_CODE)
			parse_indirect(fd);
		else
			parse_registry(fd);
		i++;
		if (i < op_tab.param_num)
			write(OUTPUT, ",", 1);
	}
}

void	no_decode(int *fd, t_op op_tab)
{
	int		i;

	i = 0;
	while (i < op_tab.param_num)
	{
		if (op_tab.arg_type[i] == T_DIR)
			parse_direct(fd, op_tab);
		else if (op_tab.arg_type[i] == T_IND)
			parse_indirect(fd);
		else
			parse_registry(fd);
		i++;
		if (i < op_tab.param_num)
			write(OUTPUT, ",", 1);
	}
}
