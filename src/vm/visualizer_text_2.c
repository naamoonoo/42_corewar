/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_text_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:02:23 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 13:10:15 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	visualizer_text_process_lived(void *data, t_process *process, int champ,
		char *champ_name)
{
	UNUSED(process);
	if (!data)
		ft_printf("A process shows that player %d (%s) is alive\n",
				champ, champ_name);
}

void	visualizer_text_memory_read(void *data, t_mem *address,
											int value, t_process *process)
{
	if (!data)
		ft_printf("%s #%d (color %.8X) read %d from %p\n",
	process->owner->name, process->pid, process->owner->color, value, address);
}

void	visualizer_text_memory_written(void *data, t_mem *address,
												int value, t_process *process)
{
	if (!data)
		ft_printf("%s #%d (color %.8X) wrote value %d to %p\n",
	process->owner->name, process->pid, process->owner->color, value, address);
}

void	visualizer_text_render(void *data, t_vm *vm)
{
	if (!data)
	{
		ft_printf("Cycle %d (%%d rounds since last decrease)\n",
				vm->total_cycles, vm->cycles_to_die, CYCLE_TO_DIE - vm->delta,
				vm->rounds_since_decrease);
		ft_printf("\tLives this round: %d\n", vm->lives_this_round);
		ft_printf("\tLast live from: %d\n", vm->last_alive);
		ft_printf("\tTotal processes: %d\n", vm->total_processes);
	}
}

void	visualizer_text_use_champs(void *data, t_arrlst *champs)
{
	UNUSED(data);
	UNUSED(champs);
}
