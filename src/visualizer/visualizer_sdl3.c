/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_sdl3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:55:04 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/17 19:55:55 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/visualizer.h"

void			visualizer_sdl_game_over(void *data, t_vm *vm)
{
	int		winner_id;
	char	*winner_name;
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	winner_id = vm->last_alive;
	winner_name = vm_get_champ_name(vm, winner_id);
	sdl->winner = winner_id - 1;
	return ;
	ft_printf("Player %d (%s) won\n", winner_id, winner_name);
}

void			visualizer_sdl_cleanup(void *data)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	while (!sdl->is_quit)
	{
		while (SDL_PollEvent(&(sdl->e)))
			if (sdl->e.type == SDL_QUIT || sdl->e.key.keysym.sym == 27)
				sdl->is_quit = 1;
		SDL_Delay(1000 / 60);
	}
	end_process(sdl);
}

static t_arrlst	*champs_from_file_array(t_set selected_cmp[MAX_PLAYERS], int n)
{
	int			champ_number;
	t_arrlst	*champions;
	t_champion	*champ;
	int			i;

	champions = ft_arrlst_new(sizeof(t_champion *));
	if (champions == NULL)
		return (NULL);
	champ_number = 1;
	i = 0;
	while (i < n)
	{
		champ = read_champion_from_file(selected_cmp[i].text);
		if (champ == NULL)
			return (NULL);
		champ->number = champ_number;
		champ->color = rand();
		if (ft_arrlst_add(champions, &champ) == NULL)
			ft_putstr_fd("Error: Failed to add champion.\n", 2);
		champ_number++;
		i++;
	}
	return (champions);
}

t_arrlst		*visualizer_sdl_select_champs(void *data)
{
	t_sdl	*sdl;
	int		i;

	sdl = (t_sdl *)data;
	sdl->ready = FALSE;
	while (!sdl->ready)
	{
		sdl = (t_sdl *)data;
		while (SDL_PollEvent(&(sdl->e)))
			event_handler(sdl);
		if (!sdl->is_running)
			return (NULL);
		SDL_RenderClear(sdl->ren);
		render_start_page(sdl);
		SDL_SetRenderDrawColor(sdl->ren, 0xda, 0xdd, 0xdf, 0);
		SDL_RenderPresent(sdl->ren);
		SDL_Delay(1000 / 60);
	}
	i = -1;
	while (++i < sdl->nb_of_p)
	{
		sdl->selected_cmp[i].text = ft_strdup(sdl->selected_cmp[i].text);
	}
	destroy_start_page(sdl);
	return (champs_from_file_array(sdl->selected_cmp, sdl->nb_of_p));
}

void			visualizer_sdl_sleep(void *data)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	SDL_Delay((sdl->winner >= 0 ? 100000 : 1000) / 60);
}
