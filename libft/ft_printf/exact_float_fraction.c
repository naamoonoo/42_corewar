/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exact_float_fraction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:42:39 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/30 20:52:26 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exact_float.h"
#include "../libft.h"

static int			is_zero(t_big_fraction *n)
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

static unsigned int	multiply(t_big_fraction *n, unsigned int multiplicand)
{
	int				i;
	unsigned int	foo;
	unsigned long	product;
	unsigned int	carry;

	if (is_zero(n))
		return (0);
	i = n->size - 1;
	carry = 0;
	while (i >= 0)
	{
		foo = n->value[i];
		product = ((unsigned long)foo * (unsigned long)multiplicand) + carry;
		carry = (product & 0xffffffff00000000) >> 32;
		n->value[i] = (int)product;
		i--;
	}
	return (carry);
}

char				*fraction_to_string(t_big_fraction *n, int precision)
{
	char	*str;
	int		i;

	if (!n)
		return (NULL);
	str = ft_strnew(precision);
	if (!str)
		return (NULL);
	i = 0;
	while (i < precision)
	{
		str[i] = '0' + multiply(n, 10);
		i++;
	}
	if (multiply(n, 10) > 4)
		str[i - 1] = str[i - 1] + 1;
	return (str);
}

static void			helper(int precision, int *i, t_big_fraction *n, char *str)
{
	while (*i < precision)
	{
		str[*i] = '0' + multiply(n, 10);
		(*i)++;
	}
}

/*
** I would give this a more descriptive name if not for norm, but it basically
** ignores leading zeros when counting the precision.
*/

char				*fraction_to_string2(t_big_fraction *n, int precision)
{
	char			*str;
	int				leading_zeros;
	unsigned int	digit;
	int				i;

	if (!n)
		return (NULL);
	leading_zeros = 0;
	digit = multiply(n, 10);
	while (!digit)
	{
		digit = multiply(n, 10);
		leading_zeros++;
	}
	str = ft_strnew(leading_zeros + precision);
	if (!str)
		return (NULL);
	ft_memset(str, '0', leading_zeros + precision);
	str[leading_zeros] = '0' + digit;
	i = 1;
	helper(precision, &i, n, str + leading_zeros);
	if (multiply(n, 10) > 4)
		str[leading_zeros + i - 1] = str[leading_zeros + i - 1] + 1;
	return (str);
}
