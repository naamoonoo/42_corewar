/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 20:15:37 by aderby            #+#    #+#             */
/*   Updated: 2017/06/14 20:49:33 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strwjoin(char **s, char *c)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = ft_strnew(1);
	while (s[i])
	{
		tmp = str;
		str = ft_strjoinf(tmp, s[i]);
		if (s[i + 1])
		{
			str = ft_strjoin(str, c);
		}
		i++;
	}
	return (str);
}
