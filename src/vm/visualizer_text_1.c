/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_text_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:02:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 13:37:05 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	visualizer_text_init(void *data, int argc, char **argv)
{
	UNUSED(data);
	UNUSED(argc);
	UNUSED(argv);
}

void	visualizer_text_instruction_read(void *data, t_mem *address)
{
	if (!data)
		ft_printf("instruction %d read at address %p\n", address->data,
				address);
}

void	visualizer_text_instruction_fired(void *data, t_mem *address)
{
	if (!data)
		ft_printf("instruction fired at address %p\n", address);
}

int		visualizer_text_program_active(void *data)
{
	UNUSED(data);
	return (TRUE);
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
