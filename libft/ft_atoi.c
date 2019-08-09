/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:04:19 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 22:39:59 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(const char *str)
{
	if (*str == '+')
		return (1);
	if (*str == '-')
		return (-1);
	return (0);
}

static int	is_whitespace(char c)
{
	if ((c == ' ') || (c == '\t'))
		return (1);
	if ((c == '\n') || (c == '\v'))
		return (1);
	if ((c == '\r') || (c == '\f'))
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		sign;
	long	result;

	while (is_whitespace(*str))
		str++;
	sign = get_sign(str);
	if (sign != 0)
	{
		str++;
		if (*str < '0' || *str > '9')
			return (0);
		else
			return (sign * ft_atoi(str));
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		while (result > 4294967296)
			result -= 4294967296;
		str++;
	}
	return (result);
}
