/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:57:56 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 22:47:06 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t size;

	size = ft_strlen(src);
	if (size >= len)
		return (ft_memcpy(dst, src, len));
	else
	{
		ft_memcpy(dst, src, size);
		ft_bzero(dst + size, len - size);
		return (dst);
	}
}
