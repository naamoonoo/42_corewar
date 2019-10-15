/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_sdl4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:55:08 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 13:52:19 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/visualizer.h"

void			visualizer_sdl_silence(t_visualizer *gv)
{
	UNUSED(gv);
}

static void		initialize_gv_functions(t_visualizer *gv)
{
	gv->init = &visualizer_sdl_init;
	gv->instruction_read = &visualizer_sdl_instruction_read;
	gv->instruction_fired = &visualizer_sdl_instruction_fired;
	gv->process_lived = &visualizer_sdl_process_lived;
	gv->memory_read = &visualizer_sdl_memory_read;
	gv->memory_written = &visualizer_sdl_memory_written;
	gv->render = &visualizer_sdl_render;
	gv->program_active = &visualizer_sdl_program_active;
	gv->game_over = &visualizer_sdl_game_over;
	gv->cleanup = &visualizer_sdl_cleanup;
	gv->select_champs = &visualizer_sdl_select_champs;
	gv->use_champs = &visualizer_sdl_use_champs;
	gv->sleep = &visualizer_sdl_sleep;
	gv->silence = &visualizer_sdl_silence;
}

t_visualizer	*visualizer_sdl_new(void)
{
	t_visualizer	*gv;
	t_sdl			*sdl;

	gv = (t_visualizer *)malloc(sizeof(t_visualizer));
	if (gv == NULL)
		return (NULL);
	sdl = sdl_init();
	if (sdl == NULL)
	{
		free(gv);
		return (NULL);
	}
	gv->data = sdl;
	initialize_gv_functions(gv);
	return (gv);
}
