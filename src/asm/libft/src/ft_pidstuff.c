/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pidstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:49:22 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 21:23:05 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

/*
** set initial flags -
** # : alternate form (ocatl prints 066, 034/// | hex prints 0x66, 0x34...)
** 0 : fill field with 0's
** - : fill the left space with fw chars
** ' ' : leave blnk before psitive number
** + : must place a sign
*/

int		set_flags(t_printf **print1, char *s, int j)
{
	while (s[j] == '#' || s[j] == '0' || s[j] == '-' ||
			s[j] == ' ' || s[j] == '+')
	{
		if (s[j] == '#')
			(*print1)->pid->f_alt = 1;
		if (s[j] == '0')
			(*print1)->pid->f_zero = 1;
		if (s[j] == '-')
			(*print1)->pid->f_ladj = 1;
		if (s[j] == ' ')
			(*print1)->pid->f_space = 1;
		if (s[j] == '+')
			(*print1)->pid->f_sign = 1;
		j++;
	}
	return (j);
}

int		set_fieldwidth(t_printf **print1, char *s, int j)
{
	int fw;

	fw = 0;
	if (ft_isdigit(s[j]))
		fw = ft_atoi(&s[j]);
	while (ft_isdigit(s[j]))
		j++;
	if (fw > 0)
		(*print1)->pid->fw = fw;
	return (j);
}

int		set_length(t_printf **print1, char *s, int j)
{
	if (ft_islengthchar(s[j]))
	{
		if ((s[j] == 'h' && s[j + 1] == 'h') ||
				(s[j] == 'l' && s[j + 1] == 'l'))
		{
			if (s[j + 1] == 'h')
				(*print1)->pid->len = L_HH;
			else if (s[j + 1] == 'l')
				(*print1)->pid->len = L_LL;
			return (j + 2);
		}
		else if (s[j] == 'h')
			(*print1)->pid->len = L_H;
		else if (s[j] == 'l')
			(*print1)->pid->len = L_L;
		else if (s[j] == 'j')
			(*print1)->pid->len = L_J;
		else if (s[j] == 'z')
			(*print1)->pid->len = L_Z;
		return (j + 1);
	}
	return (j);
}

int		set_type(t_printf **p, char *s, int j)
{
	if (ft_isconversionchar(s[j]))
	{
		(*p)->type = ((s[j] == 's' || s[j] == 'S') ? S_TYPE : (*p)->type);
		(*p)->type = ((s[j] == 'c' || s[j] == 'C') ? C_TYPE : (*p)->type);
		(*p)->type = ((s[j] == 'd' || s[j] == 'i') ? DI_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'D' ? DD_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'o' ? O_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'O' ? OO_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'u' ? U_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'U' ? UL_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'x' ? X_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'X' ? XX_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'p' ? P_TYPE : (*p)->type);
		(*p)->type = (s[j] == '%' ? PCNT_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'b' ? B_TYPE : (*p)->type);
		(*p)->type = (s[j] == 'B' ? BB_TYPE : (*p)->type);
		(*p)->pid->base = (s[j] == 'x' || s[j] == 'X' ? 16 : (*p)->pid->base);
		(*p)->pid->base = (s[j] == 'o' || s[j] == 'O' ? 8 : (*p)->pid->base);
		(*p)->pid->base = (s[j] == 'b' || s[j] == 'B' ? 2 : (*p)->pid->base);
		(*p)->pid->xbase = (s[j] == 'X' ? 1 : -1);
		FF_ALT = (s[j] == 'x' || s[j] == 'X') && FF_ALT != -1 ? 16 : FF_ALT;
		FF_ALT = (s[j] == 'o' || s[j] == 'O') && FF_ALT != -1 ? 8 : FF_ALT;
		return ((*p)->type == -1 ? -1 : j + 1);
	}
	return (-1);
}

int		set_precision(t_printf **print1, char *s, int j)
{
	int	precision;

	precision = 0;
	if (s[j] == '.')
	{
		j++;
		if (ft_isdigit(s[j]))
			precision = ft_atoi(&s[j]);
		else if (!(ft_isconversionchar(s[j]) || ft_islengthchar(s[j])))
			return (-1);
		while (ft_isdigit(s[j]))
			j++;
		(*print1)->pid->prec = precision;
	}
	return (j);
}
