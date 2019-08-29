/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:47:30 by aderby            #+#    #+#             */
/*   Updated: 2019/08/21 10:10:32 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	decode(int *fd, t_op op_tab)
{
	char	c;
	int		arg_type;
	int		i;
	char	separator;

	i = 0;
	read(INPUT, &c, 1);
	separator = SEPARATOR_CHAR;
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
			write(OUTPUT, &separator, 1);
	}
}

void	no_decode(int *fd, t_op op_tab)
{
	int		i;
	char	separator;

	i = 0;
	separator = SEPARATOR_CHAR;
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
			write(OUTPUT, &separator, 1);
	}
}
