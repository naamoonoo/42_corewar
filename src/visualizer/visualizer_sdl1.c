/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_sdl1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:54:55 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/17 19:54:56 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/visualizer.h"

void	visualizer_sdl_process_lived(void *data, t_process *process, int champ,
		char *champ_name)
{
	UNUSED(data);
	UNUSED(process);
	UNUSED(champ);
	UNUSED(champ_name);
	return ;
}

void	visualizer_sdl_memory_read(void *data, t_mem *address, int value,
		t_process *process)
{
	UNUSED(data);
	UNUSED(address);
	UNUSED(value);
	UNUSED(process);
	return ;
}

void	visualizer_sdl_memory_written(void *data, t_mem *address, int value,
		t_process *process)
{
	t_sdl	*sdl;

	UNUSED(value);
	sdl = (t_sdl *)data;
	address->owner = process->owner->filename;
	address->next->owner = process->owner->filename;
	address->next->next->owner = process->owner->filename;
	address->next->next->next->owner = process->owner->filename;
	address->is_instruction = 1;
	return ;
}

void	get_pc(t_sdl *sdl, t_vm *vm)
{
	static int	call_time = 0;
	t_process	*process;
	int			i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		vm->memory->is_pc = 0;
		if (call_time == 0)
			vm->memory->rect = (SDL_Rect){MAP_P_X + (i % 64) * BOX_W + 1,
			MAP_P_Y + (i / 64) * BOX_H + 1, BOX_W - 2, BOX_H - 2};
		vm->memory = vm->memory->next;
	}
	sdl->mem_start = vm->memory;
	process = vm->p_list;
	while (process)
	{
		process->pc->is_pc = 1;
		process = process->next;
	}
}

void	visualizer_sdl_render(void *data, t_vm *vm)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	get_pc(sdl, vm);
	while (SDL_PollEvent(&(sdl->e)))
		event_handler(sdl);
	SDL_RenderClear(sdl->ren);
	render_play_page(sdl);
	render_cycle_box(sdl, vm->total_cycles);
	sdl->winner >= 0 ? render_finish(sdl) : 0;
	SDL_SetRenderDrawColor(sdl->ren, 0xda, 0xdd, 0xdf, 0);
	SDL_RenderPresent(sdl->ren);
	return ;
}
