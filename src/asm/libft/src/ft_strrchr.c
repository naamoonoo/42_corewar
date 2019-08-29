/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 13:01:35 by aderby            #+#    #+#             */
/*   Updated: 2017/06/09 14:47:43 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s) + 1;
	while (len >= 0)
		if (s[--len] == (char)c)
			return ((char *)(s + len));
	return (NULL);
}
