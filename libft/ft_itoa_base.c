/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:34:59 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/10 19:04:01 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long n, const char *base)
{
	char	*str;
	char	*tmp;

	if (n < 0)
	{
		tmp = ft_itoa_base_u(0 - n, base);
		if (tmp == NULL)
			return (NULL);
		str = ft_strsum("-", tmp);
		free(tmp);
		return (str);
	}
	return (ft_itoa_base_u(n, base));
}
