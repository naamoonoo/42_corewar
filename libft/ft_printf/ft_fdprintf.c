/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:28:58 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/19 16:02:12 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	write_printable(int fd, t_list *printable)
{
	t_printable	*p;
	t_formatter	formatter;
	char		*str;
	int			len;

	p = (t_printable *)printable->content;
	if (p && (p->data || (p->type == '%')))
	{
		formatter = formatter_for_type(p->type);
		if (formatter)
		{
			str = (*formatter)(p);
			if (str)
			{
				len = ft_strlen(str);
				if (p->type == 'c' && *((char *)p->data) == 0)
					len = ft_max(1, p->field_width);
				write(fd, str, len);
				free(str);
				return (len);
			}
		}
	}
	return (0);
}

static int	write_printables(int fd, t_list *printables)
{
	int chars_written;

	chars_written = 0;
	while (printables)
	{
		chars_written += write_printable(fd, printables);
		printables = printables->next;
	}
	return (chars_written);
}

static int	printf_main(int fd, const char *format, va_list ap)
{
	t_list		*printables;
	int			pa;
	t_arglist	*arglist;
	int			chars_written;

	printables = read_format_string(format);
	pa = positional_args(printables);
	if (pa == -1)
		return (-1);
	arglist = build_arglist(printables, pa);
	if (arglist == NULL)
		return (-1);
	if (!withdraw_args(arglist, ap))
	{
		free_printables(&printables);
		free_arglist(&arglist);
		return (-1);
	}
	inject_args(printables, arglist, pa);
	chars_written = write_printables(fd, printables);
	free_printables(&printables);
	free_arglist(&arglist);
	return (chars_written);
}

int			ft_fdprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			result;

	va_start(ap, format);
	result = printf_main(fd, format, ap);
	va_end(ap);
	return (result);
}
