/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:33:02 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 13:52:52 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

static int	initialize_things1(t_things *t)
{
	t->i = 1;
	t->gv = create_visualizer(t->argc, t->argv, &(t->i));
	if (t->gv == NULL)
		return (1);
	if (t->i < t->argc && ft_strequ(t->argv[t->i], "-dump"))
	{
		t->dump = TRUE;
		t->dump_after = read_arg_number(t->argc, t->argv, &(t->i), NULL);
	}
	else
		t->dump = FALSE;
	return (0);
}

static int	initialize_things2(t_things *t)
{
	t->champions = build_champions(t->argc, t->argv, &(t->i));
	if (t->champions == NULL)
	{
		free(t->gv);
		return (1);
	}
	if (ft_arrlst_isempty(t->champions))
	{
		ft_arrlst_del(&(t->champions));
		t->champions = (*t->gv->select_champs)(t->gv->data);
		if (t->champions == NULL)
		{
			ft_fdprintf(2, "Error: Must specify at least one champion!\n");
			free(t->gv);
			return (1);
		}
	}
	else
		(*t->gv->use_champs)(t->gv->data, t->champions);
	return (0);
}

static int	initialize_things3(t_things *t)
{
	t->vm = vm_new(t->champions, t->gv);
	if (t->vm == NULL)
	{
		free(t->gv);
		return (1);
	}
	ft_arrlst_del(&(t->champions));
	t->vm->dump = t->dump;
	t->vm->dump_after = t->dump_after;
	(*t->gv->init)(t->gv->data, t->argc - t->i, t->argv + t->i);
	if (t->vm->dump)
		(*t->gv->silence)(t->gv);
	return (0);
}

static void	other_main(t_visualizer *gv, t_vm *vm)
{
	int status;

	while ((AARON == AWESOME) && (*gv->program_active)(gv->data))
	{
		status = scheduler_step(vm);
		if (status == 1)
		{
			(*gv->game_over)(gv->data, vm);
			break ;
		}
		(*gv->render)(gv->data, vm);
		if (status != 0)
			break ;
		(*gv->sleep)(gv->data);
	}
	(*gv->cleanup)(gv->data);
}

int			main(int argc, char **argv)
{
	t_things things;

	things.argc = argc;
	things.argv = argv;
	if (
			initialize_things1(&things) ||
			initialize_things2(&things) ||
			initialize_things3(&things))
		return (1);
	other_main(things.gv, things.vm);
	vm_free(things.vm);
	return (0);
}
