/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:21:34 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 21:22:20 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t srcsize;

	if ((dst == 0) || (src == 0))
		return (0);
	srcsize = ft_strlen(src);
	if (srcsize < dstsize)
	{
		ft_memcpy(dst, src, srcsize);
		dst[srcsize] = 0;
	}
	else
	{
		ft_memcpy(dst, src, dstsize - 1);
		if (dstsize != 0)
			dst[dstsize - 1] = 0;
	}
	return (srcsize);
}
