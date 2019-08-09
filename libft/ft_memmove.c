/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:32:52 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/04/29 21:44:36 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*sorc;
	char	*dest;

	sorc = (char *)src;
	dest = (char *)dst;
	if (dst > src)
	{
		i = (int)(len - 1);
		while (i >= 0)
		{
			dest[i] = sorc[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)(len))
		{
			dest[i] = sorc[i];
			i++;
		}
	}
	return (dst);
}
