/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_iter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:42:59 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 19:53:17 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrlst_iter(t_arrlst *arrlst, void (*f)(void *elem))
{
	int i;

	if (!arrlst)
		return ;
	i = 0;
	while (i < arrlst->size)
	{
		(*f)(arrlst->data + i * arrlst->elem_size);
		i++;
	}
}
