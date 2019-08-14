/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_text_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:02:23 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/13 21:31:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

static void		visualizer_text_process_lived(void *data, t_process *process)
{
	ft_printf("process %d lived\n", process->pid);
	UNUSED(data);
}

static void		visualizer_text_memory_read(void *data, t_mem *address, int value, t_process *process)
{
	ft_printf("%s #%d read %d from %p\n", process->owner->name, process->pid, value, address);
	UNUSED(data);
}

static void		visualizer_text_memory_written(void *data, t_mem *address, int value, t_process *process)
{
	ft_printf("%s #%d wrote value %d to %p\n", process->owner->name, process->pid, value, address);
	UNUSED(data);
}

static void		visualizer_text_update_misc(void *data, t_vm *vm)
{
	UNUSED(data);
	ft_printf("Cycle %d (%d remaining out of %d; %d round since last decrease)\n",
			vm->total_cycles, vm->cycles_to_die, CYCLE_TO_DIE - vm->delta,
			vm->rounds_since_decrease);
	ft_printf("\tLives this round: %d\n", vm->lives_this_round);
	ft_printf("\tLast live from: %d\n", vm->last_alive);
	ft_printf("\tTotal processes: %d\n", vm->total_processes);
}

t_visualizer	*visualizer_text_new()
{
	t_visualizer *gv;

	gv = (t_visualizer *)malloc(sizeof(t_visualizer));
	if (gv == NULL)
		return (NULL);
	gv->init = &visualizer_text_init;
	(*gv->init)(gv->data);
	gv->instruction_read = &visualizer_text_instruction_read;
	gv->instruction_fired = &visualizer_text_instruction_fired;
	gv->process_lived = &visualizer_text_process_lived;
	gv->memory_read = &visualizer_text_memory_read;
	gv->memory_written = &visualizer_text_memory_written;
	gv->update_misc = &visualizer_text_update_misc;
	return (gv);
}
