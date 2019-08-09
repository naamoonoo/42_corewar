/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:14:07 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/20 18:53:26 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*format_char(t_printable *p)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_strndup(p->data, 1);
	if (!str)
		return (NULL);
	if (*str)
		tmp = pad_printable(p, "", str);
	else
	{
		tmp = pad_printable(p, "", "x");
		i = 0;
		while (tmp[i])
		{
			if (tmp[i] == 'x')
				tmp[i] = 0;
			i++;
		}
	}
	free(str);
	return (tmp);
}
