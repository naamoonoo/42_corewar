/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:30:49 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 00:46:15 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

void	free_printf_fmt(t_format **fmt, int type)
{
	if (type == S_TYPE || type == WS_TYPE)
		ft_strdel(&((*fmt)->s));
	if (*fmt)
	{
		free(*fmt);
		*fmt = NULL;
	}
}

void	free_printf_pid(t_pid **pid)
{
	if (*pid)
	{
		free(*pid);
		*pid = NULL;
	}
}

void	free_all(t_printf **head)
{
	t_printf *tmp;

	if (*head)
	{
		while (*head)
		{
			if ((*head)->type == STRING_TYPE)
				ft_strdel(&((*head)->str));
			else if ((*head)->type != -1)
			{
				free_printf_fmt(&((*head)->pid->fmt), (*head)->type);
				free_printf_pid(&((*head)->pid));
			}
			tmp = *head;
			*head = (*head)->next;
			free(tmp);
		}
	}
}
