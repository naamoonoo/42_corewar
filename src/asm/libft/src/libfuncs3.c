/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfuncs3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:05:34 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 00:43:49 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

char	*ft_strfjoin(char **s1, const char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = i;
	if (*s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(new = ft_strnew(ft_strlen((char *)*s1) + ft_strlen((char *)s2))))
		return (NULL);
	while ((*s1)[i])
	{
		new[i] = (*s1)[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	ft_strdel(s1);
	return (new);
}

void	ft_strtolower(char **s)
{
	int	i;

	i = 0;
	if (*s)
	{
		while (s[0][i])
		{
			if (s[0][i] > 64 && s[0][i] < 91)
				s[0][i] += 32;
			i++;
		}
	}
}

void	ft_strdeltwo(char **s, char **s2)
{
	ft_strdel(s);
	ft_strdel(s2);
}

void	ft_strdelthree(char **s, char **s2, char **s3)
{
	ft_strdel(s);
	ft_strdel(s2);
	ft_strdel(s3);
}

char	*ft_strffjoin(char **s1, char **s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = i;
	if (*s1 == NULL || *s2 == NULL)
		return (NULL);
	if (!(new = ft_strnew(ft_strlen((char *)*s1) + ft_strlen((char *)s2))))
		return (NULL);
	while ((*s1)[i])
	{
		new[i] = (*s1)[i];
		i++;
	}
	while ((*s2)[j])
		new[i++] = (*s2)[j++];
	new[i] = '\0';
	ft_strdeltwo(s1, s2);
	return (new);
}
