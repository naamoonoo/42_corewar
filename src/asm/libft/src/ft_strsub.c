/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:54:08 by aderby            #+#    #+#             */
/*   Updated: 2017/06/22 14:51:28 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s)
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (start--)
			s++;
		ft_strncpy(str, s, len);
		str[len] = '\0';
	}
	else
		str = NULL;
	return (str);
}
