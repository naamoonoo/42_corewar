/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_sdl2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:55:00 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/17 19:55:01 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/visualizer.h"

void	visualizer_sdl_use_champs(void *data, t_arrlst *champs)
{
	t_sdl		*sdl;
	int			idx;
	t_champion	*champ;

	sdl = (t_sdl *)data;
	idx = 0;
	while (idx < champs->size)
	{
		champ = *(t_champion **)ft_arrlst_get(champs, idx);
		sdl->selected_cmp[idx].text = ft_strdup(champ->filename);
		sdl->nb_of_p += 1;
		idx++;
	}
}

void	visualizer_sdl_init(void *data, int argc, char **argv)
{
	t_sdl	*sdl;

	UNUSED(argc);
	UNUSED(argv);
	sdl = (t_sdl *)data;
	sdl->is_init = 1;
}

void	visualizer_sdl_instruction_read(void *data, t_mem *address)
{
	UNUSED(data);
	UNUSED(address);
	return ;
}

void	visualizer_sdl_instruction_fired(void *data, t_mem *address)
{
	UNUSED(data);
	UNUSED(address);
	return ;
}

int		visualizer_sdl_program_active(void *data)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	return (sdl->is_running);
}
