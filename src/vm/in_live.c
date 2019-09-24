/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/01 21:30:32 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_live(t_vm *vm, t_process *process, t_visualizer *gv)
{
	int		champ;
	char	*champ_name;

	vm->lives_this_round++;
	process->alive = TRUE;
	champ = 0 - mem_read_dir_silent(process->pc->next);
	process->pc = process->pc->next->next->next->next->next;
	champ_name = vm_get_champ_name(vm, champ);
	if (champ_name == NULL)
		return ;
	vm->last_alive = champ;
	if (gv != NULL)
		(*gv->process_lived)(gv->data, process, champ, champ_name);
}
