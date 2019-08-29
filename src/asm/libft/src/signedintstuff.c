/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signedintstuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:33:51 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 20:37:53 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static char	*ft_intmax_to_ascii(intmax_t val, int base, char *b)
{
	char		*s;
	size_t		len;
	intmax_t	tmp;
	int			flag;

	len = 1;
	tmp = val;
	while (tmp /= 10)
		len++;
	flag = 0;
	if (!(s = ft_strnew(len)))
		return (NULL);
	if (val == INTMAX_MIN)
	{
		val = (INTMAX_MIN + 1) * -1;
		flag = 1;
	}
	val *= (val < 0) ? -1 : 1;
	while (len--)
	{
		s[len] = (flag ? b[((INTMAX_MIN % base) * -1)] : b[val % base]);
		flag = 0;
		val /= base;
	}
	return (s);
}

static int	add_fieldwidth(char **str, char **chars, t_printf *print1)
{
	char	*tmp;
	char	*tmp2;

	if (chars[0][0] == '0')
	{
		if (PID->f_sign != -1 || PID->f_space != -1 || PID->fmt->im < 0)
		{
			tmp = ft_strsub(*str, 0, 1);
			tmp2 = ft_strsub(*str, 1, ft_strlen(*str) - 1);
			tmp = ft_strfjoin(&tmp, *chars);
			tmp = ft_strfjoin(&tmp, tmp2);
			ft_strdeltwo(chars, &tmp2);
		}
		else
			tmp = ft_strfjoin(chars, *str);
		ft_strdel(str);
	}
	else
	{
		tmp = ft_strfjoin((print1->pid->f_ladj != -1 ? str : chars),
				(print1->pid->f_ladj != -1 ? *chars : *str));
		ft_strdel(print1->pid->f_ladj != -1 ? chars : str);
	}
	*str = tmp;
	return ((int)ft_strlen(*str));
}

static int	add_sign(char **intmax_str, t_printf *print1)
{
	char	*sign;

	if (!(sign = ft_strnew(1)))
		return (0);
	if (print1->pid->fmt->im < 0)
	{
		sign[0] = '-';
	}
	else
		sign[0] = print1->pid->f_sign != -1 ? '+' : ' ';
	if (!(sign = ft_strfjoin(&sign, *intmax_str)))
		return (0);
	ft_strdel(intmax_str);
	*intmax_str = sign;
	return ((int)ft_strlen(*intmax_str));
}

static int	add_precision(char **intmax_str, size_t zeros)
{
	char *tmp;

	if (!(tmp = ft_strofchars('0', zeros)))
		return (0);
	if (!(tmp = ft_strfjoin(&tmp, *intmax_str)))
		return (0);
	ft_strdel(intmax_str);
	*intmax_str = tmp;
	return ((int)ft_strlen(*intmax_str));
}

int			pf_signedint(t_printf *print1)
{
	char	*s;
	char	*tmp;
	int		pad;
	int		s_len;

	if (!(s = (PID->prec == 0 && PID->fmt->im == 0) ? ft_strnew(0) :
				ft_intmax_to_ascii(NIM, PID->base, "0123456789ABCDEF")))
		return (-1);
	pad = (print1->pid->f_zero != -1 ? '0' : ' ');
	s_len = ft_strlen(s);
	if (print1->pid->prec > s_len)
		if (!(s_len = add_precision(&s, print1->pid->prec - s_len)))
			return (-1);
	if (print1->pid->f_sign != -1 || print1->pid->f_space != -1 || NIM < 0)
		if (!(s_len = add_sign(&s, print1)))
			return (-1);
	if (print1->pid->fw > s_len)
	{
		tmp = ft_strofchars(pad, print1->pid->fw - s_len);
		if (!(s_len = add_fieldwidth(&s, &tmp, print1)))
			return (-1);
	}
	ft_putstr(s);
	return (s_len);
}
