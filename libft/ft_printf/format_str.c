/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:28:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/20 15:42:43 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*format_str(t_printable *p)
{
	char *str;
	char *tmp;

	if (p->type == '\1')
		str = p->data;
	else
		str = *((char **)p->data);
	if (!str)
		return (ft_strdup("(null)"));
	if (p->precision == -1)
		str = ft_strdup(str);
	else
		str = ft_strndup(str, p->precision);
	if (!str)
		return (NULL);
	tmp = pad_printable(p, "", str);
	free(str);
	return (tmp);
}
