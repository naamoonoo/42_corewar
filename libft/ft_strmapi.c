/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:33:40 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 13:21:57 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	i;

	if (s == 0)
		return (0);
	s2 = ft_strnew(ft_strlen(s));
	if (s2 == 0)
		return (0);
	i = 0;
	while (s[i] != 0)
	{
		s2[i] = (*f)(i, s[i]);
		i++;
	}
	return (s2);
}
