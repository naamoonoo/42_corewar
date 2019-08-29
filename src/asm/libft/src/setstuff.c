/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setstuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:01:19 by aderby            #+#    #+#             */
/*   Updated: 2017/08/13 17:03:49 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		ft_islengthchar(int c)
{
	size_t	len;

	len = ft_strlen(LENGTHS);
	while (len--)
		if (c == LENGTHS[len])
			return (1);
	return (0);
}

int		ft_isconversionchar(int c)
{
	size_t len;

	len = ft_strlen(CONVERSIONS);
	while (len--)
		if (c == CONVERSIONS[len])
			return (1);
	return (0);
}

int		ft_isnumericconversionchar(int c)
{
	size_t len;

	len = ft_strlen(NUM_CONVERSIONS);
	while (len--)
		if (c == NUM_CONVERSIONS[len])
			return (1);
	return (0);
}
