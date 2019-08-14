/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:00:42 by hnam              #+#    #+#             */
/*   Updated: 2019/08/13 21:51:46 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

t_sdl	*sdl_init(void)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	if (TTF_Init())
		return (NULL);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (NULL);
	sdl->w = 2560;
	sdl->h = 1600;
	sdl->win = SDL_CreateWindow("corewar", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, sdl->w, sdl->h, SDL_WINDOW_RESIZABLE);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	sdl->font[0] = TTF_OpenFont("src/visualizer/gameboy.ttf", 80);
	sdl->font[1] = TTF_OpenFont("src/visualizer/gameboy.ttf", 24);
	SDL_RenderSetLogicalSize(sdl->ren, sdl->w, sdl->h);
	SDL_SetRenderDrawColor(sdl->ren, 169, 169, 169, 0);
	sdl->is_running = 1;
	sdl->is_quit = 0;
	sdl->cmp_selected = 0;


	sdl->is_forked = 0;
	return (sdl);
}

t_btn	*btn_init(void)
{
	t_btn *btn;

	btn = malloc(sizeof(t_btn));
	btn->start = (SDL_Rect){1550, 1380, 400, 120};
	return (btn);
}
