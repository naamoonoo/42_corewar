/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:38:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 12:32:56 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_neg(int n)
{
	int		i;
	int		places;
	char	*str;

	i = -10;
	places = 1;
	while (n <= i && places < 10)
	{
		i *= 10;
		places++;
	}
	str = ft_strnew(places + 1);
	if (str == 0)
		return (0);
	str[0] = '-';
	while (places > 0)
	{
		str[places] = '0' - n % 10;
		n = n / 10;
		places--;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	int		i;
	int		places;
	char	*str;

	if (n < 0)
		return (ft_itoa_neg(n));
	i = 10;
	places = 1;
	while (n >= i && places < 10)
	{
		i *= 10;
		places++;
	}
	str = ft_strnew(places);
	if (str == 0)
		return (0);
	while (places > 0)
	{
		str[places - 1] = '0' + n % 10;
		n /= 10;
		places--;
	}
	return (str);
}
