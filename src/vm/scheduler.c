/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:58:01 by aderby            #+#    #+#             */
/*   Updated: 2019/09/16 21:40:14 by nwhitlow         ###   ########.fr       */
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

static void	prepare_null_instructions(t_vm *vm)
{
	t_process *process_iter;

	process_iter = vm->p_list;
	while (process_iter)
	{
		if (process_iter->needs_to_be_prepared_on_the_next_cycle)
			process_prepare_instruction(process_iter, vm->gv);
		process_iter = process_iter->next;
	}
}

void		decriment_cycles(t_vm *vm, t_process **p_list, int cycle_decriment)
{
	t_process	*process;

	vm->total_processes = 0;
	process = *p_list;
	while (process)
	{
		if (process->needs_to_be_prepared_on_the_next_cycle)
		{
			process_prepare_instruction(process, vm->gv);
			process->needs_to_be_prepared_on_the_next_cycle = FALSE;
		}
		process->cycles_to_wait -= cycle_decriment;
		if (process->cycles_to_wait == 0)
		{
			if (process->instruction != NULL)
			{
				(*vm->gv->instruction_fired)(vm->gv->data, process->pc);
				process->instruction(vm, process, vm->gv);
			}
			process->needs_to_be_prepared_on_the_next_cycle = TRUE;
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
	if (vm->delta > CYCLE_TO_DIE)
		return (1);
	vm->rounds_since_decrease++;
	if (vm->lives_this_round >= NBR_LIVE
			|| vm->rounds_since_decrease >= MAX_CHECKS)
	{
		vm->delta += CYCLE_DELTA;
		vm->rounds_since_decrease = 0;
	}
	vm->cycles_to_die = CYCLE_TO_DIE - vm->delta;
	vm->lives_this_round = 0;
	return (0);
}

int			scheduler_step(t_vm *vm)
{
	int	cycles_to_wait;
	int game_over;

	if (vm->cycles_to_die <= 0)
	{
		game_over = purge(vm);
		if (game_over)
			return (1);
	}
	cycles_to_wait = get_min_cycles_to_wait(vm->p_list, vm->cycles_to_die);
	if (cycles_to_wait > 1)
		cycles_to_wait = 1;
	if (vm->cycles_to_die < 0)
		cycles_to_wait = 1;
	vm->cycles_to_die -= cycles_to_wait;
	if (vm->dump && (vm->total_cycles + cycles_to_wait > vm->dump_after))
	{
		mem_dump(vm->memory);
		return (2);
	}
	if (cycles_to_wait == 0)
		prepare_null_instructions(vm);
	else
		decriment_cycles(vm, &vm->p_list, cycles_to_wait);
	return (0);
}
