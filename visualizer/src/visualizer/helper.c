/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:02:27 by hnam              #+#    #+#             */
/*   Updated: 2019/08/18 22:39:39 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"



void	event_handler(t_sdl *sdl, t_btn *btn)
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
			&& (sdl->nb_of_p > 1));
	}
	if (KEY == SDLK_DOWN)
		sdl->is_forked = 1;
	// if (KEY == SDLK_UP)
	// 	sdl->roun = 1;
	// else if (sdl->e.key.keysym.sym == SDLK_DOWN)
	// 	parse_data(f, sdl);
	// else if (sdl->e.key.keysym.sym == SDLK_RIGHT)
	// 	f->auto_fill = 1;
	// else if (sdl->e.key.keysym.sym == SDLK_LEFT)
	// 	f->auto_fill = 0;
	(void)btn;
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
