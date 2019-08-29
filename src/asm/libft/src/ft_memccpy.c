/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 10:14:59 by aderby            #+#    #+#             */
/*   Updated: 2017/06/13 18:31:23 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char unsigned	*dstptr;
	unsigned char	*srcptr;
	size_t			i;

	i = 0;
	dstptr = (unsigned char *)dst;
	srcptr = (unsigned char *)src;
	while (i < n)
	{
		dstptr[i] = srcptr[i];
		if (srcptr[i] == (unsigned char)c)
			return (&dstptr[i] + 1);
		i++;
	}
	return (NULL);
}
