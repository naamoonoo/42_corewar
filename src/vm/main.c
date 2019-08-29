/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:33:02 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/28 02:08:43 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

/*
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
*/

t_visualizer	*create_visualizer(int argc, char **argv, int *i)
{
	if (argc == 1)
	{
		ft_putstr("usage: ./corewar [-v [text | SDL]]"
				"[[-n number] champion1.cor] ... [-dump nbr_cycles]\n");
		return (NULL);
	}
	if (ft_strequ(argv[1], "-v"))
	{
		if (argc == 2)
		{
			ft_putstr("Error: -v must be followed by an argument.\n");
			return (NULL);
		}
		else if (ft_strequ(argv[2], "text"))
		{
			*i = 3;
			return (visualizer_text_new());
		}
		else if (ft_strequi(argv[2], "sdl"))
		{
			*i = 3;
			return (visualizer_sdl_new());
		}
		ft_putstr("Error: -v must be followed by either text or SDL.\n");
		return (NULL);
	}
	else
	{
		*i = 1;
		return (visualizer_text_new());
	}
}

int			main(int argc, char **argv)
{
	t_visualizer	*gv;
	t_arrlst	*champions;
	t_vm	*vm;
	int	i;

	gv = create_visualizer(argc, argv, &i);
	if (gv == NULL)
		return (1);
	champions = build_champions(argc, argv, &i);
	if (champions == NULL)
	{
		free(gv);
		return (1);
	}
	(*gv->init)(gv->data, argc - i + 1, argv + i - 1); // TODO check failure
	if (ft_arrlst_isempty(champions))
	{
		ft_arrlst_del(&champions);
		champions = (*gv->select_champs)(gv->data);
		if (champions == NULL)
		{
			ft_printf("Error: Must specify at least one champion!\n");
			free(gv);
			return (1);
		}
	}
	vm = vm_new(champions);
	if (vm == NULL)
	{
//		ft_arrlst_free(&champions, free_champion);
		free(gv);
		return (1);
	}
	ft_arrlst_del(&champions);
	vm->gv = gv;
//	print_vm(vm);
	while ((*gv->program_active)(gv->data))
	{
		int status = scheduler_step(vm);
		if (status == 1)
			(*gv->game_over)(gv->data, vm);
		if (status != 0)
			break;
		(*gv->render)(gv->data, vm);
		// SDL_Delay(1000 / 60);
		// usleep(1000000 / 60);
	}
	(*gv->cleanup)(gv->data);
	vm_free(vm);
	return (0);
}
