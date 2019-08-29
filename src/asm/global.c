/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:17:44 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:03:45 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	(*g_parse_function[])(t_tree **t, char **split, int l_num, int *fd) =
{
	NULL,
	&parse_name_comment,
	&parse_label,
	&parse_error,
	&parse_instruction,
};
