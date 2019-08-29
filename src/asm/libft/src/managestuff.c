/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managestuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 18:33:33 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 00:43:21 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

t_printf	*newlist(void)
{
	t_printf	*new;

	if (!(new = (t_printf *)ft_memalloc(sizeof(t_printf))))
		return (NULL);
	new->type = -1;
	new->function = NULL;
	new->str = NULL;
	new->pid = NULL;
	new->next = NULL;
	return (new);
}

int			storechar_prints(t_printf **print1, const char c, int ret)
{
	int len;

	if ((*print1)->type == -1)
		(*print1)->type = STRING_TYPE;
	else if ((*print1)->type != STRING_TYPE)
	{
		(*print1)->next = newlist();
		*print1 = (*print1)->next;
		(*print1)->type = STRING_TYPE;
	}
	if ((*print1)->str == NULL)
	{
		if (!((*print1)->str = ft_strnew(1)))
			return (-1);
		(*print1)->str[0] = c;
	}
	else
	{
		len = ft_strlen((*print1)->str);
		if (!((*print1)->str = ft_strfresize(&((*print1)->str), len + 1)))
			return (-1);
		(*print1)->str[len] = c;
	}
	return (ret + 1);
}
