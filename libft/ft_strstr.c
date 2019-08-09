/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:38:49 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/03 14:46:16 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	hash(const char *str, int len)
{
	short	hash;
	int		i;

	hash = 0;
	i = 0;
	while (i < len)
	{
		hash = hash << 8;
		hash += str[i];
		hash %= HMODULUS;
		i++;
	}
	if (hash < 0)
		hash += HMODULUS;
	return (hash);
}

static short	left_base_offset(int len)
{
	short offset;

	offset = 1;
	while (len > 1)
	{
		offset = offset << 8;
		offset %= HMODULUS;
		len--;
	}
	return (offset);
}

static void		roll_hash(const char *str, short *hash, int len, short lbo)
{
	*hash -= (lbo * *str);
	*hash %= HMODULUS;
	*hash = *hash << 8;
	*hash += str[len];
	*hash %= HMODULUS;
	if (*hash < 0)
		*hash += HMODULUS;
}

char			*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		nlen;
	int		hlen;
	short	hash_data[3];

	if ((haystack == 0) || (needle == 0))
		return (0);
	nlen = ft_strlen(needle);
	hlen = ft_strlen(haystack);
	if (nlen > hlen)
		return (0);
	hash_data[0] = hash(needle, nlen);
	hash_data[1] = hash(haystack, nlen);
	hash_data[2] = left_base_offset(nlen);
	i = 0;
	while (1)
	{
		if (hash_data[1] == hash_data[0])
			if (ft_strnequ(haystack + i, needle, nlen))
				return (char *)(haystack + i);
		if (i == hlen - nlen)
			return (0);
		roll_hash(haystack + i, &hash_data[1], nlen, hash_data[2]);
		i++;
	}
}
