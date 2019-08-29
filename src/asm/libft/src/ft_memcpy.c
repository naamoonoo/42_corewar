/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:14:15 by aderby            #+#    #+#             */
/*   Updated: 2017/06/07 10:19:06 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*destptr;
	const char	*srcptr;

	destptr = dst;
	srcptr = src;
	while (n > 0)
	{
		*destptr = *srcptr;
		destptr++;
		srcptr++;
		n--;
	}
	return (dst);
}
