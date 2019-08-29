/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:29:07 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 00:22:24 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static char	*add_fieldwidth(char **s, int f_ladj, int spaces)
{
	char	*tmp;

	if (!(tmp = ft_strofchars(' ', spaces)))
		return (NULL);
	if (f_ladj != -1)
	{
		if (!(*s = ft_strfjoin(s, tmp)))
			return (NULL);
		ft_strdel(&tmp);
	}
	else
	{
		if (!(tmp = ft_strfjoin(&tmp, *s)))
			return (NULL);
		ft_strdel(s);
		*s = tmp;
	}
	return (*s);
}

int			pf_string(t_printf *print1)
{
	char	*s;
	int		n;

	if (print1->pid->fmt->s == NULL)
		if (!(print1->pid->fmt->s = ft_strdup("(null)")))
			return (-1);
	if (print1->pid->prec != -1)
	{
		s = ft_strsub(print1->pid->fmt->s, 0, print1->pid->prec);
		ft_strdel(&(print1->pid->fmt->s));
		print1->pid->fmt->s = s;
	}
	n = PID->fw - ft_strlen(print1->pid->fmt->s);
	if (n > 0)
		if (!(PID->fmt->s = add_fieldwidth(&(PID->fmt->s), PID->f_ladj, n)))
			return (-1);
	ft_putstr(print1->pid->fmt->s);
	return (ft_strlen(print1->pid->fmt->s));
}
