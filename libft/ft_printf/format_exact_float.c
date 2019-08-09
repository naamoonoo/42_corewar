/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_exact_float.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 20:48:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 23:22:18 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "exact_float.h"

char		*format_special(t_exact_float *n, char flags)
{
	flags = 0;
	if (n->type == 'i')
	{
		if (n->sign == 1)
			return (ft_strdup("inf"));
		else
			return (ft_strdup("-inf"));
	}
	else if (n->type == 'n')
		return (ft_strdup("NaN"));
	return (NULL);
}

int			is_zero(t_exact_float *n)
{
	int	i;

	if (n->integer.size <= 0 && n->fraction.size <= 0)
		return (1);
	i = 0;
	while (i < n->integer.size)
	{
		if (n->integer.value[i])
			return (0);
		i++;
	}
	i = 0;
	while (i < n->fraction.size)
	{
		if (n->fraction.value[i])
			return (0);
		i++;
	}
	return (1);
}

int			round_up_check(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] <= '9')
		i++;
	if ((*str)[i] <= '9')
		return (0);
	while (i >= 0)
	{
		if ((*str)[i] >= '9')
			(*str)[i] = '0';
		else if ((*str)[i] != '.')
		{
			(*str)[i] = (*str)[i] + 1;
			return (0);
		}
		i--;
	}
	tmp = *str;
	*str = ft_strnew(ft_strlen(*str) + 1);
	(*str)[0] = '1';
	ft_strcpy((*str) + 1, tmp);
	free(tmp);
	return (1);
}

static int	load_strings(t_exact_float *n, t_printable *p)
{
	char *tmp;

	if (p->precision == -1)
		p->precision = 6;
	if (!(n->integer_str))
		n->integer_str = integer_to_string(&(n->integer));
	if (!(n->integer_str))
		return (0);
	if (!(n->fraction_str))
		n->fraction_str = fraction_to_string(&(n->fraction), p->precision);
	if (!(n->fraction_str))
		return (0);
	if (p->precision == 0)
	{
		tmp = fraction_to_string(&(n->fraction), 1);
		if (*tmp >= '4')
			n->integer_str[ft_strlen(n->integer_str) - 1]++;
		free(tmp);
	}
	return (1);
}

char		*format_f(t_exact_float *n, t_printable *p)
{
	char *str;
	char *tmp;

	if (!load_strings(n, p))
		return (NULL);
	if (p->precision || (p->flags & ALTFORM))
	{
		str = ft_strsum(n->integer_str, ".");
		tmp = ft_strsum(str, n->fraction_str);
	}
	else
	{
		str = NULL;
		tmp = ft_strdup(n->integer_str);
	}
	free(str);
	round_up_check(&tmp);
	str = pad_number(p, num_prefix(p->flags, n->sign == -1), tmp);
	free(tmp);
	return (str);
}
