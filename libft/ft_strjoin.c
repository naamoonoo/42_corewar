/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:47:07 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 21:16:05 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1len;

	if ((s1 == 0) || (s2 == 0))
		return (0);
	s1len = ft_strlen(s1);
	str = ft_strnew(s1len + ft_strlen(s2));
	if (str == 0)
		return (0);
	ft_strcpy(str, s1);
	ft_strcpy(str + s1len, s2);
	return (str);
}
