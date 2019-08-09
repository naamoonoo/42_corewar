/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_add_arrlst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:58:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/06 12:05:38 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arrlst_add_arrlst(t_arrlst *lst, t_arrlst *src, int off, int amount)
{
	void *arr;

	if (!lst || !src)
		return (NULL);
	if (off + amount > src->size)
		amount = src->size - off;
	arr = src->data + off * src->elem_size;
	return (ft_arrlst_add_arr(lst, arr, amount));
}
