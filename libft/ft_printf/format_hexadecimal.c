/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hexadecimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:01:39 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/30 13:06:51 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	byte_size(ARGSIZE size)
{
	if (size == SIZE_CHAR)
		return (sizeof(char));
	if (size == SIZE_SHORT)
		return (sizeof(short));
	if (size == SIZE_INT)
		return (sizeof(int));
	if (size == SIZE_LONG)
		return (sizeof(long));
	if (size == SIZE_LONGLONG)
		return (sizeof(long long));
	return (sizeof(int));
}

static char	hex_to_char(unsigned char c, int uppercase)
{
	if (c < 10)
		return (c + '0');
	else
		return (c - 10 + (uppercase ? 'A' : 'a'));
}

static char	*value_to_hex(char *ptr, int size, int uppercase)
{
	int				i;
	char			*hex;
	unsigned char	c;

	hex = ft_strnew(size * 2 + 1);
	if (hex == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		c = ptr[i];
		hex[2 * i] = hex_to_char(c & 0xf, uppercase);
		hex[2 * i + 1] = hex_to_char(c / 16, uppercase);
		i++;
	}
	i = 2 * size - 1;
	while (i > 0 && hex[i] == '0')
		i--;
	hex[i + 1] = 0;
	ft_strrev(hex);
	return (hex);
}

static int	format_hex_str(t_printable *p, char **hex, int uppercase)
{
	char	*tmp;
	char	*prefix;

	if (p->precision != -1)
	{
		p->flags &= ~ZEROPAD;
		if (!pad_left(hex, p->precision))
			return (0);
	}
	if (p->flags & ALTFORM && !ft_strequ(*hex, "0") && !ft_strequ(*hex, ""))
		prefix = uppercase ? "0X" : "0x";
	else
		prefix = "";
	if (!(p->flags & ZEROPAD))
	{
		tmp = *hex;
		*hex = ft_strsum(prefix, *hex);
		prefix = "";
		free(tmp);
	}
	tmp = *hex;
	*hex = pad_printable(p, prefix, *hex);
	free(tmp);
	return (1);
}

char		*format_hexadecimal(t_printable *p)
{
	char	*mem;
	int		size;
	int		uppercase;
	char	*hex;

	mem = p->data;
	size = byte_size(size_of_type(p->type, p->modifier));
	uppercase = (p->type == 'X');
	hex = value_to_hex(mem, size, uppercase);
	if (ft_strequ(hex, "0") && p->precision == 0)
	{
		free(hex);
		hex = ft_strdup("");
	}
	if (format_hex_str(p, &hex, uppercase))
		return (hex);
	else
		return (NULL);
}
