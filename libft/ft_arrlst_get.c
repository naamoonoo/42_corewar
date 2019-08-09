/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:53:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 21:53:48 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arrlst_get(t_arrlst *arrlst, int index)
{
	if (!arrlst)
		return (NULL);
	return (arrlst->data + index * arrlst->elem_size);
}
