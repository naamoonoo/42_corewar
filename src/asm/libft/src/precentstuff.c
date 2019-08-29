/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precentstuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 18:27:46 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 00:29:28 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static char	*add_fieldwidth(char **s, int f_ladj, int spaces, char pad)
{
	char	*tmp;

	if (!(tmp = ft_strofchars(pad, spaces)))
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

int			pf_percent(t_printf *print1)
{
	char	pad;
	char	*s;
	int		s_len;
	int		spaces;

	if (!(s = ft_strdup("%")))
		return (-1);
	pad = (print1->pid->f_zero != -1) ? '0' : ' ';
	pad = (print1->pid->f_ladj != -1) ? ' ' : pad;
	s_len = 1;
	spaces = print1->pid->fw - s_len;
	if (spaces > 0)
		if (!(s = add_fieldwidth(&s, print1->pid->f_ladj, spaces, pad)))
			return (-1);
	ft_putstr(s);
	return (ft_strlen(s));
}

int			pf_character(t_printf *print1)
{
	int	fw;

	fw = 0;
	if (print1->pid->f_ladj != -1)
	{
		ft_putchar(print1->pid->fmt->c);
		while (++fw < print1->pid->fw)
			ft_putchar(' ');
	}
	else
	{
		while (++fw < print1->pid->fw)
			ft_putchar(' ');
		ft_putchar(print1->pid->fmt->c);
	}
	return (fw);
}
