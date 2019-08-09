/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:45:57 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/09 16:08:22 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*s2;

	s2 = (char *)(malloc((len + 1) * sizeof(char)));
	if (s2 == 0)
		return (0);
	ft_memcpy(s2, s1, len);
	s2[len] = 0;
	return (s2);
}
