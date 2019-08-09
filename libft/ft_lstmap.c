/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:33:34 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 20:03:25 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;
	t_list *lst2;

	if (lst == 0)
		return (0);
	new_list = f(lst);
	lst2 = new_list;
	while (lst->next != 0)
	{
		lst = lst->next;
		lst2->next = f(lst);
		lst2 = lst2->next;
	}
	lst2->next = 0;
	return (new_list);
}
