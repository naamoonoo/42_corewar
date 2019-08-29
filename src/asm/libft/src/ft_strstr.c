/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:42:28 by aderby            #+#    #+#             */
/*   Updated: 2017/06/09 14:53:48 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i])
	{
		if (big[i] == little[j])
			j++;
		else
		{
			i -= j;
			j = 0;
		}
		if (little[j] == '\0')
			return ((char *)big + i - j + 1);
		i++;
	}
	return (NULL);
}
