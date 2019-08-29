/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:42:28 by aderby            #+#    #+#             */
/*   Updated: 2017/06/12 17:07:37 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	int i;
	int j;
	int l;

	i = 0;
	j = 0;
	l = (int)n;
	if (*little == '\0')
		return ((char *)big);
	while ((big[i]) && (--l >= 0))
	{
		if (big[i] == little[j])
			j++;
		else
		{
			i -= j;
			l += j;
			j = 0;
		}
		if (little[j] == '\0')
			return ((char *)big + i - j + 1);
		i++;
	}
	return (NULL);
}
