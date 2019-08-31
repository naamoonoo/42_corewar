/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 20:26:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/29 11:05:58 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	in_live(t_vm *vm, t_process *process, t_visualizer *gv)
{
	int		champ;
	char	*champ_name;

	process->alive = TRUE;
	champ = 0 - mem_read_dir_silent(process->pc->next);
	process->pc = process->pc->next->next->next->next->next;
	champ_name = vm_get_champ_name(vm, champ);
	if (champ_name == NULL)
		return ;
	vm->last_alive = champ;
	vm->lives_this_round++;
	// ft_printf("A process shows that player %d (%s) is alive\n",
	// 		champ, champ_name);
	(void)champ;
	(void)champ_name;
	if (gv != NULL)
		(*gv->process_lived)(gv->data, process);
}
