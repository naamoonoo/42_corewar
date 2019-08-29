/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:21:25 by aderby            #+#    #+#             */
/*   Updated: 2017/06/10 14:53:08 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sptr;
	unsigned char	b;

	b = (unsigned char)c;
	sptr = (unsigned char *)s;
	while (n > 0)
	{
		if (*sptr == b)
			return ((void *)sptr);
		sptr++;
		n--;
	}
	return (NULL);
}
