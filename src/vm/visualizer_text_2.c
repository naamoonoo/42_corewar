/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_text_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:02:23 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/21 22:06:25 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

static void		visualizer_text_process_lived(void *data, t_process *process)
{
	ft_printf("process %d lived\n", process->pid);
	UNUSED(data);
}

static void		visualizer_text_memory_read(void *data, t_mem *address,
											int value, t_process *process)
{
	ft_printf("%s #%d (color %.8X) read %d from %p\n",
	process->owner->name, process->pid, process->owner->color, value, address);
	UNUSED(data);
}

static void		visualizer_text_memory_written(void *data, t_mem *address,
												int value, t_process *process)
{
	ft_printf("%s #%d (color %.8X) wrote value %d to %p\n",
	process->owner->name, process->pid, process->owner->color, value, address);
	UNUSED(data);
}

static void		visualizer_text_render(void *vdata, t_vm *vm)
{
	t_visualizer_text_data *data;

	data = (t_visualizer_text_data *)vdata;
	ft_printf("Cycle %d (%%d rounds since last decrease)\n",
			vm->total_cycles, vm->cycles_to_die, CYCLE_TO_DIE - vm->delta,
			vm->rounds_since_decrease);
	ft_printf("\tLives this round: %d\n", vm->lives_this_round);
	ft_printf("\tLast live from: %d\n", vm->last_alive);
	ft_printf("\tTotal processes: %d\n", vm->total_processes);
	if (data->dump && (vm->total_cycles >= data->dump_after))
	{
		data->running = FALSE;
		mem_dump(vm->memory);
	}
}

t_visualizer	*visualizer_text_new(void)
{
	t_visualizer *gv;
	t_visualizer_text_data *data;

	gv = (t_visualizer *)malloc(sizeof(t_visualizer));
	if (gv == NULL)
		return (NULL);
	data = (t_visualizer_text_data *)malloc(sizeof(t_visualizer_text_data));
	if (data == NULL)
	{
		free(gv);
		return (NULL);
	}
	gv->data = data;
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
	return (gv);
}
