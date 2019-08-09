/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:58:55 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 21:16:50 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		word_count(const char *s, int slen, char c)
{
	int	word_count;
	int	in_word;
	int	i;

	word_count = 0;
	i = 0;
	in_word = 0;
	while (1)
	{
		if (i < slen && s[i] != c)
			in_word = 1;
		else
		{
			if (in_word == 1)
			{
				in_word = 0;
				word_count++;
			}
		}
		if (s[i] == 0)
			return (word_count);
		i++;
	}
}

static void		norm_is_dumb(int *start, int *end, int i)
{
	if (*start == -1)
		*start = i;
	*end = i;
}

static int		load_words(const char *s, int slen, char c, char **words)
{
	int	word;
	int	start;
	int	end;
	int	i;

	i = 0;
	start = -1;
	end = -1;
	word = 0;
	while (1)
	{
		if (i < slen && s[i] != c)
			norm_is_dumb(&start, &end, i);
		else if (start != -1)
		{
			words[word] = ft_strsub(s, start, end - start + 1);
			if (words[word] == 0)
				return (0);
			start = -1;
			word++;
		}
		if (s[i] == 0)
			return (1);
		i++;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	int		count;
	char	**words;

	if (s == 0)
		return (0);
	count = word_count(s, ft_strlen(s), c);
	words = (char **)malloc((count + 1) * sizeof(words));
	if (words == 0)
		return (0);
	words[count] = 0;
	if (load_words(s, ft_strlen(s), c, words) == 0)
		return (0);
	return (words);
}
