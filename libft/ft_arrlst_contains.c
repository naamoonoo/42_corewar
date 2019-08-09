/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_contains.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:13:36 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/06 12:14:09 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrlst_contains(t_arrlst *arrlst, void *elem)
{
	int		i;
	void	*loc;

	if (!arrlst || !elem)
		return (0);
	i = 0;
	while (i < arrlst->size)
	{
		loc = arrlst->data + i * arrlst->elem_size;
		if (!ft_memcmp(loc, elem, arrlst->elem_size))
			return (1);
		i++;
	}
	return (0);
}
