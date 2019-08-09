/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:36:06 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/06 12:38:32 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arrlst_set(t_arrlst *list, int index, void *data)
{
	void *dst;

	if (!list || !data)
		return (NULL);
	if (index < 0 || index >= list->size)
		return (NULL);
	dst = list->data + index * list->elem_size;
	ft_memcpy(dst, data, list->elem_size);
	return (dst);
}
