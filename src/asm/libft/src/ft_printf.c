/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 16:32:29 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 21:24:04 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static int	initialize_printfs(t_printf **print1, t_printf **print2)
{
	if (!(*print1 = newlist()))
		return (0);
	*print2 = *print1;
	return (1);
}

static int	print_everything(t_printf **print2)
{
	int			i;
	t_printf	*tmp;

	i = 0;
	tmp = *print2;
	while (tmp)
	{
		if (tmp->type == STRING_TYPE)
		{
			ft_putstr(tmp->str);
			i += ft_strlen(tmp->str);
		}
		else
		{
			i += tmp->function(tmp);
		}
		tmp = tmp->next;
	}
	return (i);
}

int			ft_printf(char *fmt, ...)
{
	va_list		args;
	t_printf	*print1;
	t_printf	*print2;
	int			ret;

	va_start(args, fmt);
	if (!(initialize_printfs(&print1, &print2)))
		return (-1);
	ret = 0;
	while (fmt[ret])
	{
		if (fmt[ret] == '%')
			ret = store_formatmods(&print1, &fmt[ret], &args, ret);
		else
			ret = storechar_prints(&print1, fmt[ret], ret);
		if (ret == -1)
			break ;
	}
	if (ret != 0 && ret != -1)
		ret = print_everything(&print2);
	free_all(&print2);
	return (ret);
}
