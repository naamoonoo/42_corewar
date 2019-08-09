/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:48:06 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/11 12:07:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*new_printable(void)
{
	t_list		*l;
	t_printable	*p;

	p = (t_printable *)malloc(sizeof(t_printable));
	if (p == NULL)
		return (NULL);
	l = ft_lstnew(0, sizeof(t_printable *));
	if (l == NULL)
		return (NULL);
	p->flags = 0;
	p->field_width_arg = -1;
	p->field_width = 0;
	p->precision_arg = -1;
	p->precision = -1;
	p->type = 0;
	p->data_arg = -1;
	p->data = 0;
	l->content = p;
	return (l);
}

void	free_printables(t_list **printables)
{
	t_printable *p;

	if ((printables == NULL) || (*printables == NULL))
		return ;
	p = (*printables)->content;
	if (p != NULL)
		free(p);
	free_printables(&((*printables)->next));
	free(*printables);
	*printables = 0;
}
