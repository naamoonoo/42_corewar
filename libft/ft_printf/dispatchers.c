/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatchers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:30:45 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/10 12:01:36 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ARGSIZE		size_of_type(char type, char modifier)
{
	int		i;
	t_sizer	sizer;

	i = 0;
	while (g_type_formatters[i].type != 0)
	{
		if (g_type_formatters[i].type == type)
		{
			sizer = g_type_formatters[i].sizer;
			if (sizer == NULL)
				return (0);
			return ((*sizer)(modifier));
		}
		i++;
	}
	return (0);
}

t_reader	reader_for_size(ARGSIZE size)
{
	int	i;

	if (size == 0)
		return (NULL);
	i = 0;
	while (g_type_readers[i].size != 0)
	{
		if (g_type_readers[i].size == size)
			return (g_type_readers[i].reader);
		i++;
	}
	return (NULL);
}

t_reader	reader_for_type(char type, char modifier)
{
	ARGSIZE	size;

	size = size_of_type(type, modifier);
	if (size == 0)
		return (NULL);
	return (reader_for_size(size));
}

t_formatter	formatter_for_type(char type)
{
	int	i;

	i = 0;
	while (g_type_formatters[i].type != 0)
	{
		if (g_type_formatters[i].type == type)
			return (g_type_formatters[i].formatter);
		i++;
	}
	return (NULL);
}
