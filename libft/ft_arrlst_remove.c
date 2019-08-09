/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:33:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 20:18:09 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrlst_remove(t_arrlst *arrlst, void *elem)
{
	int		i;
	void	*dst;
	void	*src;

	if (!arrlst || !elem)
		return (-1);
	i = 0;
	while (i < arrlst->size)
	{
		dst = arrlst->data + i * arrlst->elem_size;
		if (!ft_memcmp(dst, elem, arrlst->elem_size))
		{
			src = arrlst->data + (i + 1) * arrlst->elem_size;
			ft_memmove(dst, src, (arrlst->size - i - 1) * arrlst->elem_size);
			arrlst->size--;
			return (i);
		}
		i++;
	}
	return (-1);
}
