/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:09:13 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 18:26:39 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arrlst	*ft_arrlst_new(int datum_size)
{
	t_arrlst *arrlst;

	arrlst = (t_arrlst *)malloc(sizeof(t_arrlst));
	if (!arrlst)
		return (NULL);
	arrlst->elem_size = datum_size;
	arrlst->alloc_size = 0;
	arrlst->size = 0;
	arrlst->data = NULL;
	return (arrlst);
}
