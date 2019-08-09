/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:19:13 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/10 16:29:24 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		ft_swapbytes(str + i, str + len - 1 - i);
		i++;
	}
}
