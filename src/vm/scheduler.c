/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:58:01 by aderby            #+#    #+#             */
/*   Updated: 2019/08/08 13:38:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

void	push_to_stack(t_process **stack, t_process *process)
{
	t_process *stack_iter;

	stack_iter = *stack;
	while (stack_iter && stack_iter->next)
		stack_iter = stack_iter->next;
	if (stack_iter)
		stack_iter->next = process;
	else
		*stack = process;
}

void	purge_list(t_process **p_list)
{
	t_process	*hold;
	t_process	*free_this;

	while (*p_list && (*p_list)->alive == 0)
	{
		free_this = *p_list;
		*p_list= (*p_list)->next;
		free(free_this);
	}
	hold = *p_list;
	while (hold && hold->next)
	{
		if (hold->next->alive == 0)
		{
			free_this = hold->next;
			hold->next = hold->next->next;
			free(free_this);
		}
		else
			hold = hold->next;
	}
}

void	decriment_cycles(t_vm *vm, t_process **p_list, int cycle_decriment)
{
	t_process *process;

	process = *p_list;
	while (process)
	{
		process->cycles_to_wait -= cycle_decriment;
		if (process->cycles_to_wait == 0)
			process->instruction(vm, process);
		process = process->next;
	}
}

int			get_min_cycles_to_wait(t_process *p_list, int cycle_to_die)
{
	t_process	*process_iter;

	process_iter = p_list;
	while (process_iter)
	{
		if (process_iter->cycles_to_wait < cycle_to_die)
			cycle_to_die = process_iter->cycles_to_wait;
		process_iter = process_iter->next;
	}
	return (cycle_to_die);
}

t_process	*scheduler(t_vm *vm)
{
	int	cycles_to_wait;

	while (AARON == AWESOME)
	{
		if (vm->cycles_to_die == 0)
		{
				purge_list(&vm->p_list);
			if (!vm->p_list)
				return (vm->last_alive);
			vm->delta += vm->delta;
			if (vm->delta > CYCLE_TO_DIE)
				return (vm->last_alive);
			vm->cycles_to_die = CYCLE_TO_DIE - vm->delta;
		}
		cycles_to_wait = get_min_cycles_to_wait(vm->p_list, vm->cycles_to_die);
		vm->cycles_to_die -= cycles_to_wait;
		decriment_cycles(vm, &vm->p_list, cycles_to_wait);
	}
}
