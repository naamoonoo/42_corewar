/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 18:06:27 by bpierce           #+#    #+#             */
/*   Updated: 2017/06/20 15:13:46 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char(const char a, const char c)
{
	if (a == c)
		return (1);
	return (0);
}

static char	*front_trim(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	if (str)
	{
		while (is_char(str[i], c))
			i++;
		if (str[i] == '\0')
			return (ft_strnew(1));
	}
	if (!(new = ft_strdup(&str[i])))
		return (NULL);
	return (new);
}

static char	*back_trim(char *str, char c)
{
	int		i;
	char	*new;

	if (str)
	{
		if (!(i = ft_strlen(str)))
			return (NULL);
		i--;
		while (is_char(str[i], c))
			i--;
		if (!(new = ft_strsub(str, 0, (i + 1))))
			return (NULL);
	}
	else
		new = NULL;
	return (new);
}

char		*ft_strctrim(char *str, char c, int i)
{
	char	*tmp;
	char	*tmp2;

	if (*str)
	{
		if (i == 0)
		{
			if ((tmp = front_trim(str, c)))
				return (tmp);
		}
		else if (i == 1)
		{
			if ((tmp = back_trim(str, c)))
				return (tmp);
		}
		else if (i == 2)
		{
			tmp = front_trim(str, c);
			tmp2 = back_trim(tmp, c);
			free(tmp);
			return (tmp2);
		}
	}
	return (NULL);
}
