/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:22:54 by aderby            #+#    #+#             */
/*   Updated: 2019/06/26 12:34:53 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, char *s3)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, ft_strlen(s1));
	ft_memmove(str + ft_strlen(s1), s2, ft_strlen(s2));
	ft_memmove(str + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3));
	return (str);
}
