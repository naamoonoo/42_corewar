/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:30:15 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/02 14:25:56 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	int		start;
	int		end;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	start = dstlen;
	end = ft_min(dstlen + srclen, dstsize - 1);
	if (start < end)
	{
		ft_memcpy(dst + start, src, end - start);
		dst[end] = 0;
	}
	return (ft_min(dstsize, dstlen) + srclen);
}
