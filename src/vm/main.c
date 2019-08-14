/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:33:02 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/12 14:34:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

static t_vm	*free_vm_and_return_null(t_vm *vm)
{
	free(vm);
	return (NULL);
}

static t_vm	*build_vm(int argc, char **argv)
{
	t_arrlst	*champions;
	t_vm		*vm;
	int			i;

	vm = vm_new();
	if (vm == NULL)
		return (NULL);
	i = 1;
	if (ft_strequ(argv[i], "-dump"))
	{
		vm->dump = TRUE;
		vm->dump_after = read_arg_number(argc, argv, &i, vm);
	}
	champions = build_champions(argc, argv, i);
	if (champions == NULL)
		free_vm_and_return_null(vm);
	if (ft_arrlst_isempty(champions))
	{
		ft_printf("Error: Must specify at least one champion!\n");
		free_vm_and_return_null(vm);
	}
	if (vm_add_champions(vm, champions) == -1)
		free_vm_and_return_null(vm);
	ft_arrlst_del(&champions);
	return (vm);
}

static void	print_vm(t_vm *vm)
{
	int			i;
	t_champion	*info;
	t_process	*p;

	ft_printf("Virtual machine with %d champions:\n", vm->num_champions);
	i = 0;
	while (i < vm->num_champions)
	{
		info = vm->champions[i];
		ft_printf("\t#%d \"%s\" (%s)\n",
				info->number, info->name, info->comment);
		i++;
	}
	ft_printf("and processes:\n");
	p = vm->p_list;
	while (p != NULL)
	{
		ft_printf("\tProcess %d at %p\n", p->pid, p->pc);
		p = p->next;
	}
}

int			main(int argc, char **argv)
{
	t_vm	*vm;
	int		winner_id;
	char	*winner_name;

	if (argc == 1)
	{
		ft_putstr("usage: ./corewar [-dump nbr_cycles]"
				"[[-n number] champion1.cor] ...\n");
		exit(1);
	}
	vm = build_vm(argc, argv);
	if (vm == NULL)
		exit(1);
	print_vm(vm);
	if (scheduler(vm) == 0)
	{
		winner_id = vm->last_alive;
		winner_name = vm_get_champ_name(vm, winner_id);
		ft_printf("Player %d (%s) won\n", winner_id, winner_name);
	}
	else
		mem_dump(vm->memory);
	vm_free(vm);
	return (0);
}
