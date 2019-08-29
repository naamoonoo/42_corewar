/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_arg_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:14:04 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:04:32 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		ide_mixed_type(t_tree *t, char *arg, t_arg_type type, t_tree *instruct)
{
	if (type == (T_DIR | T_IND | T_REG))
	{
		if (arg[0] == 'r')
			return (ide_arg_type(t, arg, T_REG, instruct));
		type--;
	}
	if (type == (T_DIR | T_IND))
	{
		if (ft_strchr(arg, DIRECT_CHAR))
			return (ide_arg_type(t, arg, T_DIR, instruct));
		else
			return (ide_arg_type(t, arg, T_IND, instruct));
	}
	if (type == (T_IND | T_REG))
	{
		if (arg[0] == 'r')
			return (ide_arg_type(t, arg, T_REG, instruct));
		else
			return (ide_arg_type(t, arg, T_IND, instruct));
	}
	else if (arg[0] == 'r')
		return (ide_arg_type(t, arg, T_REG, instruct));
	return (ide_arg_type(t, arg, T_DIR, instruct));
}

int		ide_arg_type(t_tree *t, char *arg, t_arg_type type, t_tree *instruction)
{
	if (type == T_REG)
		return (parse_reg_type(arg, t, instruction));
	if (type == T_IND)
		return (parse_indirect_type(arg, t, instruction));
	if (type == T_DIR)
		return (parse_direct_type(arg, t, instruction));
	else
		return (ide_mixed_type(t, arg, type, instruction));
}
