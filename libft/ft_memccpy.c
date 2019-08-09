/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:31:47 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 22:01:55 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *loc;

	loc = dst;
	while (n > 0)
	{
		*loc = *((unsigned char *)src);
		loc++;
		if (*((unsigned char *)src) == (unsigned char)c)
			return (loc);
		src++;
		n--;
	}
	return (0);
}
