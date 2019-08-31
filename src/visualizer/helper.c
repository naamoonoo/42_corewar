/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:02:27 by hnam              #+#    #+#             */
/*   Updated: 2019/08/31 00:05:00 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/visualizer.h"

int	is_clicked(t_sdl *sdl, SDL_Rect btn)
{
	if ((BTN_X >= btn.x && BTN_X <= btn.x + btn.w) &&
		(BTN_Y >= btn.y && BTN_Y <= btn.y + btn.h))
		return (1);
	return (0);
}

void	event_handler(t_sdl *sdl)
{
	if (sdl->e.type == SDL_QUIT)
		sdl->is_quit = 1;
	if (sdl->e.type == SDL_QUIT || sdl->e.key.keysym.sym == SDLK_ESCAPE)
		sdl->is_running = 0;
	if (sdl->ready == 0 && sdl->e.type == SDL_MOUSEBUTTONDOWN)
	{
		select_player(sdl);
		unselect_player(sdl);
		change_page(sdl);
		sdl->ready = (is_clicked(sdl, (SDL_Rect){1610, 1300, 300, 80})
			&& (sdl->nb_of_p > 0));
		sdl->ready ? destroy_start_page(sdl) : 0;
	}
	if (KEY == SDLK_UP)
		sdl->in_show = 1;
	if (KEY == SDLK_DOWN)
		sdl->in_show = 0;
}

void	end_process(t_sdl *sdl)
{
	int i;

	i = -1;
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	// while (++i < NUM_OF_INFO)
	// 	SDL_DestroyTexture(sdl->tex[i]);
	TTF_Quit();
	SDL_Quit();
	free(sdl);
}

// char	*get_champ_name(t_sdl *sdl, int idx)
// {
// 	char	**tmp;
// 	int		i;

// 	i = -1;
// 	tmp = ft_strsplit(sdl->champs[sdl->page * 10 + idx], '/');
// 	while (tmp[i])
// 		i++;
// 	sdl->curr_champs[idx] = ft_strdup[]
// }

void		free_char_pp(char **arr)
{
	int	i;

	i = -1;
	while(arr[++i])
		free(arr[i]);
	free(arr);
}
