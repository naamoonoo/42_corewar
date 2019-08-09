/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_non_printable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 21:39:19 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 23:21:11 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		len_non_printable(char *str)
{
	int len;

	len = 0;
	while (*str)
	{
		if (ft_isprint(*str))
			len++;
		else
			len += 4;
		str++;
	}
	return (len);
}

void	write_non_printable(char *str, unsigned char unprintable)
{
	str[0] = '\\';
	str[1] = 'x';
	if (unprintable > 159)
		str[2] = 'a' - 10 + unprintable / 16;
	else
		str[2] = '0' + unprintable / 16;
	if (unprintable % 16 > 9)
		str[3] = 'a' - 10 + unprintable % 16;
	else
		str[3] = '0' + unprintable % 16;
}

char	*convert_non_printable(char *str)
{
	char	*new_str;
	int		len;
	int		i;

	len = len_non_printable(str);
	new_str = ft_strnew(len);
	if (!new_str)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (ft_isprint(*str))
		{
			new_str[i] = *str;
			i++;
		}
		else
		{
			write_non_printable(new_str + i, *str);
			i += 4;
		}
		str++;
	}
	return (new_str);
}

char	*format_non_printable(t_printable *p)
{
	char *str;
	char *tmp;

	str = *((char **)p->data);
	if (p->precision == -1)
		str = ft_strdup(str);
	else
		str = ft_strndup(str, p->precision);
	if (!str)
		return (NULL);
	tmp = convert_non_printable(str);
	free(str);
	if (!tmp)
		return (NULL);
	str = pad_printable(p, "", tmp);
	free(tmp);
	return (str);
}
