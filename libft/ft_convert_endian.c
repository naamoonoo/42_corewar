/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_endian.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:17:56 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/01 14:23:17 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_convert_endian(void *data, int size, int sub_size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_memrev(data + i, sub_size);
		i += sub_size;
	}
}
