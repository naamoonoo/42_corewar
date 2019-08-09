/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:58:54 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 11:58:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const void *s, int c)
{
	char *str;
	char *match;

	str = (char *)s;
	match = 0;
	while (*str != 0)
	{
		if (*str == (unsigned char)c)
			match = str;
		str++;
	}
	if (c == 0)
		return (str);
	return (match);
}
