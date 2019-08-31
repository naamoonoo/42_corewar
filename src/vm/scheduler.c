/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:58:01 by aderby            #+#    #+#             */
/*   Updated: 2019/08/29 11:06:25 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

/*
** void	push_to_stack(t_process **stack, t_process *process)
** {
** 	t_process *stack_iter;
**
** 	stack_iter = *stack;
** 	while (stack_iter && stack_iter->next)
** 		stack_iter = stack_iter->next;
** 	if (stack_iter)
** 		stack_iter->next = process;
** 	else
** 		*stack = process;
** }
*/

void		purge_list(t_process **p_list)
{
	t_process	*hold;
	t_process	*free_this;

	while (*p_list && (*p_list)->alive == 0)
	{
		free_this = *p_list;
		*p_list = (*p_list)->next;
		free(free_this);
	}
	hold = *p_list;
	if (hold)
		hold->alive = 0;
	while (hold && hold->next)
	{
		if (hold->next->alive == 0)
		{
			free_this = hold->next;
			hold->next = hold->next->next;
			free(free_this);
		}
		else if (!(hold->next->alive = 0))
			hold = hold->next;
	}
}

void		decriment_cycles(t_vm *vm, t_process **p_list, int cycle_decriment)
{
	// ft_printf("Waiting %d cycles\n", cycle_decriment);
	t_process	*process;

	vm->total_processes = 0;
	process = *p_list;
	while (process)
	{
		process->cycles_to_wait -= cycle_decriment;
		if (process->cycles_to_wait == 0)
		{
			if (process->instruction != NULL)
			{
				(*vm->gv->instruction_fired)(vm->gv->data, process->pc);
				process->instruction(vm, process, vm->gv);
			}
			process_prepare_instruction(process, vm->gv);
		}
		process = process->next;
		vm->total_processes++;
	}
	vm->total_cycles += cycle_decriment;
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

static int	purge(t_vm *vm)
{
	purge_list(&vm->p_list);
	if (!vm->p_list)
		return (1);
	vm->rounds_since_decrease++;
	if (vm->lives_this_round > NBR_LIVE
			|| vm->rounds_since_decrease >= MAX_CHECKS)
	{
		vm->delta += CYCLE_DELTA;
		vm->rounds_since_decrease = 0;
	}
	if (vm->delta > CYCLE_TO_DIE) // TODO the vm should run one more cycle and then re-purge
		return (1);
	vm->cycles_to_die = CYCLE_TO_DIE - vm->delta;
	vm->lives_this_round = 0;
	return (0);
}

int			scheduler_step(t_vm *vm)
{
	int	cycles_to_wait;
	int game_over;

	if (vm->cycles_to_die == 0)
	{
		game_over = purge(vm);
		if (game_over)
			return (1);
	}
	cycles_to_wait = get_min_cycles_to_wait(vm->p_list, vm->cycles_to_die);
	vm->cycles_to_die -= cycles_to_wait;
	decriment_cycles(vm, &vm->p_list, cycles_to_wait);
	return (0);
}
