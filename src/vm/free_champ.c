/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:44:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/16 21:45:16 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	free_champion(t_champion *champ)
{
	free(champ->name);
	free(champ->comment);
	free(champ);
}

void	free_champions(t_arrlst *champions)
{
	int			i;
	t_champion	*champ;

	i = 0;
	while (i < champions->size)
	{
		champ = *(t_champion **)ft_arrlst_get(champions, i);
		free(champ);
		i++;
	}
	free(champions);
}
