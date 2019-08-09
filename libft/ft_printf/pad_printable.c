/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_printable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:55:30 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 15:31:50 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		pad_left(char **str, size_t width)
{
	size_t	len;
	char	*newstr;

	if (!str || !(*str))
		return (0);
	len = ft_strlen(*str);
	if (len < width)
	{
		newstr = malloc(width * sizeof(char));
		if (!newstr)
			return (0);
		ft_memset(newstr, '0', width);
		ft_strcpy(newstr + width - len, *str);
		free(*str);
		*str = newstr;
	}
	return (1);
}

char	*num_prefix(char flags, int negative)
{
	if (negative)
		return ("-");
	else if (flags & SIGNSPACE)
		return (" ");
	else if (flags & SIGNFORCE)
		return ("+");
	else
		return ("");
}

char	*pad_printable(t_printable *p, const char *prefix, const char *str)
{
	char	*result;
	int		pad_location;

	if (!p || !prefix || !str)
		return (NULL);
	if (p->field_width > (int)(ft_strlen(prefix) + ft_strlen(str)))
	{
		result = ft_strnew(p->field_width + 1);
		if (!result)
			return (NULL);
		if (p->flags & ZEROPAD)
			ft_memset(result, '0', p->field_width);
		else
			ft_memset(result, ' ', p->field_width);
		result[p->field_width] = 0;
		ft_memcpy(result, prefix, ft_strlen(prefix));
		if (p->flags & RIGHTPAD)
			pad_location = ft_strlen(prefix);
		else
			pad_location = p->field_width - ft_strlen(str);
		ft_memcpy(result + pad_location, str, ft_strlen(str));
		return (result);
	}
	else
		return (ft_strsum(prefix, str));
}

char	*pad_number(t_printable *p, const char *sign, const char *str)
{
	char *tmp;
	char *result;

	if (p->flags & ZEROPAD)
		return (pad_printable(p, sign, str));
	else
	{
		tmp = ft_strsum(sign, str);
		result = pad_printable(p, "", tmp);
		free(tmp);
		return (result);
	}
}
