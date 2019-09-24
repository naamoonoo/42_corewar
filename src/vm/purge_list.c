/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by aderby            #+#    #+#             */
/*   Updated: 2019/09/16 21:43:20 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void		purge_list(t_process **p_list)
{
	t_process	*hold;
	t_process	*free_this;

	while (*p_list && (*p_list)->alive == 0)
	{
		free_this = *p_list;
		*p_list = (*p_list)->next;
		free(free_this);
	}
	hold = *p_list;
	if (hold)
		hold->alive = 0;
	while (hold && hold->next)
	{
		if (hold->next->alive == 0)
		{
			free_this = hold->next;
			hold->next = hold->next->next;
			free(free_this);
		}
		else if (!(hold->next->alive = 0))
			hold = hold->next;
	}
}
