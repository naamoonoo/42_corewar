/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 09:48:11 by aderby            #+#    #+#             */
/*   Updated: 2019/06/03 14:21:45 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
{
	int i;
	int	cw;

	i = 0;
	cw = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			cw++;
		}
		s++;
	}
	return (cw);
}

static int		ft_next(const char *s, char c)
{
	int len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ptrptr;
	int		cw;
	int		i;

	ptrptr = NULL;
	if (s)
	{
		i = 0;
		cw = count_words(s, c);
		ptrptr = (char **)malloc((sizeof(char *) * cw) + 1);
		if (!ptrptr)
			return (NULL);
		while (cw--)
		{
			while (*s == c && *s != '\0')
				s++;
			ptrptr[i] = ft_strsub(s, 0, ft_next(s, c));
			if (!ptrptr[i])
				return (NULL);
			s = s + ft_next(s, c);
			i++;
		}
		ptrptr[i] = NULL;
	}
	return (ptrptr);
}
