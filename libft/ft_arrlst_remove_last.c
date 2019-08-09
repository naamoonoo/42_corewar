/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_remove_last.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:56:50 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/06 12:05:51 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrlst_remove_last(t_arrlst *arrlst, int amount)
{
	if (!arrlst || amount <= 0)
		return ;
	arrlst->size = arrlst->size - amount;
}
