/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:00:42 by hnam              #+#    #+#             */
/*   Updated: 2019/08/18 22:42:24 by hnam             ###   ########.fr       */
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
	sdl->ready = 0;
	sdl->nb_of_p = 0;
	sdl->tmp = NULL;
	sdl->fd = open("vm_champs/champlist.txt", O_RDONLY);
	get_file(sdl->fd, &(sdl->tmp));
	close(sdl->fd);
	sdl->champs = ft_strsplit(sdl->tmp, '\n');
	sdl->page = 0;
	sdl->is_forked = 0;
	return (sdl);
}
