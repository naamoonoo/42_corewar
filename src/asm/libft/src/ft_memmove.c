/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:46:31 by aderby            #+#    #+#             */
/*   Updated: 2017/06/10 14:55:38 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*destptr;
	unsigned char	*srcptr;
	size_t			i;

	i = 0;
	destptr = (unsigned char *)dst;
	srcptr = (unsigned char *)src;
	if (destptr > srcptr)
	{
		while (i < len)
		{
			destptr[len - 1] = srcptr[len - 1];
			len--;
		}
		return (dst);
	}
	else
		while (i < len)
		{
			destptr[i] = srcptr[i];
			i++;
		}
	return (dst);
}
