/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:04:19 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 12:50:34 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(char c)
{
	if (c == '+')
		return (1);
	if (c == '-')
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

static int	pop_number(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		while (result > 4294967296)
			result -= 4294967296;
		i++;
	}
	ft_memmove(str, str + i, ft_strlen(str + i) + 1);
	return (result);
}

int			ft_pop_atoi(char *str)
{
	int		sign;
	int		i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	sign = get_sign(str[i]);
	if (sign == 0)
		sign = 1;
	else
	{
		i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	ft_memmove(str, str + i, ft_strlen(str + i) + 1);
	return (sign * pop_number(str));
}
