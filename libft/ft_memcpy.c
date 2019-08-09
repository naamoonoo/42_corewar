/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:31:56 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/04/29 21:32:41 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *loc;

	loc = dst;
	while (n > 0)
	{
		*loc = *((char *)src);
		loc++;
		src++;
		n--;
	}
	return (dst);
}
