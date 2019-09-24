/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:39:18 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/16 21:43:11 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

char		*vm_get_champ_name(t_vm *vm, int champ_id)
{
	int i;

	i = 0;
	while (i < vm->num_champions)
	{
		if (vm->champions[i]->number == champ_id)
			return (vm->champions[i]->name);
		i++;
	}
	return (NULL);
}

static int	vm_add_champion(t_vm *vm, t_champion *champ, int separation, int i)
{
	t_mem		*champ_start;
	t_process	*champ_process;

	vm->champions[i] = champ;
	champ_start = mem_ptr_add(vm->memory, separation * i);
	mem_write_from_buffer(champ_start, champ->bytecode, champ->size, champ);
	champ_process = process_new(champ->number, champ_start);
	champ_process->owner = champ;
	if (champ_process == NULL)
		return (-1);
	champ_process->next = vm->p_list;
	vm->p_list = champ_process;
	process_prepare_instruction(champ_process, vm->gv);
	return (0);
}

static int	vm_add_champions(t_vm *vm, t_arrlst *champions)
{
	int			i;
	t_champion	*champ;
	int			champ_separation;
	int			highest_pid;

	if (champions->size > MAX_PLAYERS)
		return (ft_error("Error: Too many champions!\n", -1));
	vm->num_champions = champions->size;
	champ_separation = MEM_SIZE / vm->num_champions;
	highest_pid = 1;
	i = 0;
	while (i < champions->size)
	{
		champ = *(t_champion **)ft_arrlst_get(champions, i);
		if (vm_add_champion(vm, champ, champ_separation, i) == -1)
			return (-1);
		if (champ->number > highest_pid)
			highest_pid = champ->number;
		i++;
	}
	vm->last_alive = vm->champions[vm->num_champions - 1]->number;
	vm->next_available_pid = highest_pid + 1;
	return (0);
}

t_vm		*vm_new(t_arrlst *champions, t_visualizer *gv)
{
	t_vm *vm;

	vm = (t_vm *)malloc(sizeof(t_vm));
	if (vm == NULL)
		return (NULL);
	vm->p_list = NULL;
	vm->memory = mem_block_create(MEM_SIZE);
	if (vm->memory == NULL)
	{
		free(vm);
		return (NULL);
	}
	vm->lives_this_round = 0;
	vm->rounds_since_decrease = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->delta = 0;
	vm->total_cycles = 0;
	vm->gv = gv;
	if (vm_add_champions(vm, champions) == -1)
	{
		free(vm);
		return (NULL);
	}
	return (vm);
}

void		vm_free(t_vm *vm)
{
	int			i;
	t_process	*ded;

	i = 0;
	while (i < vm->num_champions)
	{
		free_champion(vm->champions[i]);
		i++;
	}
	mem_block_free(vm->memory);
	while (vm->p_list != NULL)
	{
		ded = vm->p_list;
		vm->p_list = ded->next;
		free(ded);
	}
	free(vm);
}
