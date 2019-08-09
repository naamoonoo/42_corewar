/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exact_float_integer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:37:30 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/30 20:52:34 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exact_float.h"
#include "../libft.h"

static int			is_zero(t_big_integer *n)
{
	int	i;

	i = 0;
	if (n->size <= 0)
		return (1);
	while (i < n->size)
	{
		if (n->value[i])
			return (0);
		i++;
	}
	return (1);
}

static unsigned int	divide(t_big_integer *n, unsigned int divisor)
{
	int				i;
	unsigned int	dividend;
	unsigned int	quotient;
	unsigned long	remainder;

	remainder = 0;
	i = n->size - 1;
	while (i >= 0)
	{
		dividend = n->value[i];
		quotient = ((unsigned long)dividend + (remainder << 32)) / divisor;
		remainder = n->value[i] - quotient * divisor;
		n->value[i] = quotient;
		i--;
	}
	return (remainder);
}

char				*integer_to_string(t_big_integer *n)
{
	char	*str;
	int		length;
	int		i;

	if (!n)
		return (NULL);
	if (is_zero(n))
		return (ft_strdup("0"));
	length = 10 * n->size;
	str = ft_strnew(length);
	if (!str)
		return (NULL);
	i = length;
	while (i > 0 && !is_zero(n))
	{
		i--;
		str[i] = '0' + divide(n, 10);
	}
	ft_memmove(str, str + i, length - i);
	str[length - i] = 0;
	return (str);
}
