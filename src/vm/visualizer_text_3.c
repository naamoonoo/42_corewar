/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_text_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:30:26 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 14:06:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void			visualizer_text_cleanup(void *data)
{
	UNUSED(data);
}

t_arrlst		*visualizer_text_select_champs(void *data)
{
	UNUSED(data);
	return (NULL);
}

void			visualizer_text_sleep(void *data)
{
	UNUSED(data);
}

void			visualizer_text_silence(t_visualizer *gv)
{
	gv->data = "Hello correctors! How are you doing? Having a good day?";
}

t_visualizer	*visualizer_text_new(void)
{
	t_visualizer *gv;

	gv = (t_visualizer *)malloc(sizeof(t_visualizer));
	if (gv == NULL)
		return (NULL);
	gv->init = &visualizer_text_init;
	gv->instruction_read = &visualizer_text_instruction_read;
	gv->instruction_fired = &visualizer_text_instruction_fired;
	gv->process_lived = &visualizer_text_process_lived;
	gv->memory_read = &visualizer_text_memory_read;
	gv->memory_written = &visualizer_text_memory_written;
	gv->render = &visualizer_text_render;
	gv->program_active = &visualizer_text_program_active;
	gv->game_over = &visualizer_text_game_over;
	gv->cleanup = &visualizer_text_cleanup;
	gv->select_champs = &visualizer_text_select_champs;
	gv->use_champs = &visualizer_text_use_champs;
	gv->sleep = &visualizer_text_sleep;
	gv->silence = &visualizer_text_silence;
	gv->data = NULL;
	return (gv);
}
