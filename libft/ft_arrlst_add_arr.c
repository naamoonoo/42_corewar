/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_add_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:03:54 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/06 12:22:02 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arrlst_add_arr(t_arrlst *arrlst, void *src, int amount)
{
	void *tmp;
	void *dst;

	if (!arrlst || !src)
		return (NULL);
	if (arrlst->size + amount > arrlst->alloc_size)
	{
		tmp = arrlst->data;
		arrlst->data = malloc((arrlst->size + amount) * arrlst->elem_size);
		if (!arrlst->data)
		{
			arrlst->data = tmp;
			return (NULL);
		}
		ft_memcpy(arrlst->data, tmp, arrlst->size * arrlst->elem_size);
		arrlst->alloc_size = arrlst->size + amount;
		free(tmp);
	}
	dst = arrlst->data + arrlst->size * arrlst->elem_size;
	ft_memcpy(dst, src, amount * arrlst->elem_size);
	arrlst->size += amount;
	return (dst);
}
