/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 11:28:42 by aderby            #+#    #+#             */
/*   Updated: 2017/06/07 10:38:20 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *sptr1;
	unsigned char *sptr2;

	sptr1 = (unsigned char *)s1;
	sptr2 = (unsigned char *)s2;
	while ((n > 0) && (*sptr1 == *sptr2))
	{
		n--;
		sptr1++;
		sptr2++;
	}
	if (n == 0)
		return (0);
	return (*sptr1 - *sptr2);
}
