/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4darraynew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 23:46:55 by aderby            #+#    #+#             */
/*   Updated: 2019/05/22 23:47:08 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	***ft_4darraynew(int width, int height, int depth)
{
	char	***array;
	int		i;

	if (!(array = malloc(sizeof(char **) * (depth + 1))))
		return (NULL);
	i = 0;
	while (i < depth)
	{
		if (!(array[i] = ft_arraynew(width, height)))
			return (NULL);
	}
	if (!(array[i] = ft_arraynew(0, 0)))
		return (NULL);
	array[i][0][0] = '\0';
	return (array);
}
