/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:41:22 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/04/30 13:49:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		max;
	int		nlen;
	char	*hay;

	if (ft_strlen(haystack) > len)
		max = len - ft_strlen(needle);
	else
		max = ft_strlen(haystack) - ft_strlen(needle);
	nlen = ft_strlen(needle);
	i = 0;
	while (i <= max)
	{
		if (ft_strncmp(haystack + i, needle, nlen) == 0)
		{
			hay = (char *)(haystack + i);
			return (hay);
		}
		i++;
	}
	return (0);
}
