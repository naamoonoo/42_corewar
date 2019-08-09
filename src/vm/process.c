/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:36:58 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/08 16:00:04 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

t_process	*process_new(int pid, t_mem *pc)
{
	t_process	*process;
	int			i;

	process = malloc(sizeof(t_process));
	process->pid = pid;
	process->registers[0] = 0 - pid;
	process->carry = 0;
	i = 2;
	while (i <= REG_NUMBER)
	{
		process->registers[i] = 0;
		i++;
	}
	process->pc = pc;
	process->instruction = NULL;
	process->alive = FALSE;
	process->next = NULL;
	process->cycles_to_wait = 0;

	return (process);
}
