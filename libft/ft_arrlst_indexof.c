/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_indexof.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:29:19 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 20:18:00 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrlst_indexof(t_arrlst *arrlst, void *elem)
{
	int		i;
	void	*loc;

	if (!arrlst || !elem)
		return (-1);
	i = 0;
	while (i < arrlst->size)
	{
		loc = arrlst->data + i * arrlst->elem_size;
		if (!ft_memcmp(loc, elem, arrlst->elem_size))
			return (i);
		i++;
	}
	return (-1);
}
