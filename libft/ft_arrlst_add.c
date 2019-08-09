/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:12:52 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 20:06:56 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arrlst_add(t_arrlst *arrlst, void *new)
{
	void *tmp;
	void *dst;

	if (!arrlst || !new)
		return (NULL);
	if (arrlst->size == arrlst->alloc_size)
	{
		tmp = arrlst->data;
		arrlst->data = malloc((arrlst->alloc_size + 1) * arrlst->elem_size);
		if (!arrlst->data)
		{
			arrlst->data = tmp;
			return (NULL);
		}
		ft_memcpy(arrlst->data, tmp, arrlst->size * arrlst->elem_size);
		arrlst->alloc_size++;
		free(tmp);
	}
	dst = arrlst->data + arrlst->size * arrlst->elem_size;
	ft_memcpy(dst, new, arrlst->elem_size);
	arrlst->size++;
	return (dst);
}
