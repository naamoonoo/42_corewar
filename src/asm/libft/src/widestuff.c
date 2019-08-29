/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:03:59 by aderby            #+#    #+#             */
/*   Updated: 2017/08/14 03:39:57 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static wchar_t	*adjust_precision(wchar_t **ws, int precision)
{
	wchar_t *tmp;

	if (!(tmp = ft_wstrsub(*ws, 0, precision)))
		return (NULL);
	free(*ws);
	*ws = NULL;
	return (tmp);
}

int				pf_widestr(t_printf *print1)
{
	char	*fw;
	int		len;
	int		n;

	len = ft_wstrlen(print1->pid->fmt->ws);
	if (print1->pid->prec != -1)
		if (!(PID->fmt->ws = adjust_precision(&(PID->fmt->ws), PID->prec)))
			return (-1);
	n = PID->fw - ft_wstrlen(PID->fmt->ws);
	if (n > 0)
		if (!(fw = ft_strofchars(' ', n)))
			return (-1);
	if (PID->f_ladj != -1)
		ft_putwstr(PID->fmt->ws);
	n > 0 ? ft_putstr(fw) : 0;
	if (PID->f_ladj == -1)
		ft_putwstr(PID->fmt->ws);
	return (ft_wstrlen(PID->fmt->ws) + (n > 0 ? ft_strlen(fw) : 0));
}
