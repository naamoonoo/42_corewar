/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:20:40 by aderby            #+#    #+#             */
/*   Updated: 2017/06/10 15:00:28 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_neg(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static int		get_len(int n)
{
	int len;

	len = 1;
	if (n < 0)
		len++;
	while (n > 9 || n < -9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char			*ptr;
	int				i;
	int				isneg;

	if ((ptr = ft_strnew(get_len(n))) == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	isneg = check_neg(n);
	n *= isneg;
	i = 0;
	if (n == 0)
		ptr[i++] = '0';
	while (n > 0)
	{
		ptr[i++] = n % 10 + '0';
		n /= 10;
	}
	if (isneg == -1)
		ptr[i++] = '-';
	ptr[i] = '\0';
	ft_strrev(ptr);
	return (ptr);
}
