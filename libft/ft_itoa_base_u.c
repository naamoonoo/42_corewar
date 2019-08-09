/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:48:44 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/10 19:25:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_base(unsigned long long n, int base)
{
	int digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		n /= base;
		digits++;
	}
	return (digits);
}

char		*ft_itoa_base_u(unsigned long long n, const char *base)
{
	int		digits;
	int		base_size;
	char	*str;

	base_size = ft_strlen(base);
	if (base_size < 2)
		return (NULL);
	digits = digits_base(n, base_size);
	str = ft_strnew(digits);
	if (!str)
		return (NULL);
	while (digits > 0)
	{
		str[digits - 1] = base[n % base_size];
		n /= base_size;
		digits--;
	}
	return (str);
}
