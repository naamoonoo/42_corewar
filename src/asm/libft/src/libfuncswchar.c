/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfuncswchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:10:04 by aderby            #+#    #+#             */
/*   Updated: 2017/08/14 16:37:15 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

size_t		ft_wstrlen(wchar_t *s)
{
	wchar_t	*tmp;

	tmp = s;
	while (*tmp)
		tmp++;
	return (tmp - s);
}

int			num_of_bytes(unsigned int ui)
{
	if (ui <= 127)
		return (1);
	else if (ui <= 2047)
		return (2);
	else if (ui <= 65535)
		return (3);
	return (4);
}

wchar_t		*ft_wstrsub(wchar_t *ws, size_t start, size_t len)
{
	wchar_t	*new;
	size_t	i;

	if (ws == NULL)
		return (NULL);
	i = 0;
	if (!(new = ft_wstrnew(len)))
		return (NULL);
	while (ws[start] && i < len)
	{
		new[i] = ws[start];
		i++;
		start++;
	}
	new[i] = L'\0';
	return (new);
}

void		ft_putwchar(wchar_t wi)
{
	unsigned int	ui;

	ui = (unsigned int)wi;
	if (ui < 128)
		ft_putchar(ui);
	else if (ui < 2048)
	{
		ft_putchar(192 | (ui >> 6 & 63));
		ft_putchar(128 | (ui & 63));
	}
	else if (ui < 65536)
	{
		ft_putchar(224 | (ui >> 12 & 63));
		ft_putchar(128 | (ui >> 6 & 63));
		ft_putchar(128 | (ui & 63));
	}
	else
	{
		ft_putchar(240 | (ui >> 18 & 63));
		ft_putchar(128 | (ui >> 12 & 63));
		ft_putchar(128 | (ui >> 6 & 63));
		ft_putchar(128 | (ui & 63));
	}
}

wchar_t		*ft_wstrdup(wchar_t *ws)
{
	wchar_t	*tmp;
	int		i;

	if (!(tmp = ft_wstrnew(ft_wstrlen(ws))))
		return (NULL);
	i = 0;
	while (ws[i])
	{
		tmp[i] = ws[i];
		i++;
	}
	tmp[i] = L'\0';
	return (tmp);
}
