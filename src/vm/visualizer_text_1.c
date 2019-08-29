/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_text_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:02:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/21 22:10:23 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	visualizer_text_init(void *vdata, int argc, char **argv)
{
	t_visualizer_text_data *data;
	int i;

	data = (t_visualizer_text_data *)vdata;
	i = 1;
	if (i < argc && ft_strequ(argv[i], "-dump"))
	{
		data->dump = TRUE;
		data->dump_after = read_arg_number(argc, argv, &i, NULL);
	}
	else
		data->dump = FALSE;
	data->running = TRUE;
}

void	visualizer_text_instruction_read(void *data, t_mem *address)
{
	ft_printf("instruction %d read at address %p\n", address->data, address);
	UNUSED(data);
}

void	visualizer_text_instruction_fired(void *data, t_mem *address)
{
	ft_printf("instruction fired at address %p\n", address);
	UNUSED(data);
}

int		visualizer_text_program_active(void *vdata)
{
	t_visualizer_text_data *data;

	data = (t_visualizer_text_data *)vdata;
	return (data->running);
}

void	visualizer_text_game_over(void *vdata, t_vm *vm)
{
	int		winner_id;
	char	*winner_name;

	UNUSED(vdata);
	winner_id = vm->last_alive;
	winner_name = vm_get_champ_name(vm, winner_id);
	ft_printf("Player %d (%s) won\n", winner_id, winner_name);
}

void	visualizer_text_cleanup(void *data)
{
	free(data);
}

t_arrlst	*visualizer_text_select_champs(void *data)
{
	UNUSED(data);
	return (NULL);
}
