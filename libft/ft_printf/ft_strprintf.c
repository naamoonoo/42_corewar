/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:28:58 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/20 12:55:53 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	append_printable(char **str, t_list *printable)
{
	t_printable	*p;
	t_formatter	formatter;
	char		*print;
	char		*tmp;

	p = (t_printable *)printable->content;
	if (p)
	{
		if (!p->data && (p->type != '%'))
			return ;
		formatter = formatter_for_type(p->type);
		if (formatter)
		{
			print = (*formatter)(p);
			tmp = ft_strsum(*str, print);
			if (tmp)
			{
				free(*str);
				free(print);
				*str = tmp;
			}
		}
	}
}

static char	*write_printables(t_list *printables)
{
	char *result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (printables)
	{
		append_printable(&result, printables);
		if (!result)
			return (NULL);
		printables = printables->next;
	}
	return (result);
}

static char	*strprintf_main(const char *format, va_list ap)
{
	t_list		*printables;
	int			pa;
	t_arglist	*arglist;
	char		*result;

	printables = read_format_string(format);
	pa = positional_args(printables);
	if (pa == -1)
		return (NULL);
	arglist = build_arglist(printables, pa);
	if (arglist == NULL)
		return (NULL);
	if (!withdraw_args(arglist, ap))
	{
		free_printables(&printables);
		free_arglist(&arglist);
		return (NULL);
	}
	inject_args(printables, arglist, pa);
	result = write_printables(printables);
	free_printables(&printables);
	free_arglist(&arglist);
	return (result);
}

char		*ft_strprintf(const char *format, ...)
{
	va_list		ap;
	char		*result;

	va_start(ap, format);
	result = strprintf_main(format, ap);
	va_end(ap);
	return (result);
}
