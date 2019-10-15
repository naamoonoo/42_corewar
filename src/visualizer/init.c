/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:00:42 by hnam              #+#    #+#             */
/*   Updated: 2019/09/24 19:57:10 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "../../include/visualizer.h"

void	get_champ_name(t_sdl *sdl)
{
	char	*tmp;
	int		fd;
	int		i;

	sdl->nb_of_p = 0;
	sdl->page = 0;
	tmp = NULL;
	if ((fd = open("vm_champs/champlist.txt", O_RDONLY)) < 0)
		exit(1);
	get_file(fd, &(tmp));
	close(fd);
	sdl->champs = ft_strsplit(tmp, '\n');
	free(tmp);
	i = -1;
	while (++i < 4)
	{
		sdl->selected_cmp[i].text = NULL;
		sdl->score[i] = 0;
	}
	sdl->selected_cmp[0].color = C_P1;
	sdl->selected_cmp[1].color = C_P2;
	sdl->selected_cmp[2].color = C_P3;
	sdl->selected_cmp[3].color = C_P4;
}

t_sdl	*sdl_init(void)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	if (TTF_Init())
		return (NULL);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (NULL);
	sdl->win = SDL_CreateWindow("corewar", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	sdl->font[0] = TTF_OpenFont("src/visualizer/gameboy.ttf", 80);
	sdl->font[1] = TTF_OpenFont("src/visualizer/Ubuntu-M.ttf", 12);
	SDL_RenderSetLogicalSize(sdl->ren, WIDTH, HEIGHT);
	SDL_SetRenderDrawColor(sdl->ren, 169, 169, 169, 0);
	sdl->winner = -1;
	sdl->in_show = 0;
	sdl->is_running = 1;
	sdl->is_quit = 0;
	sdl->ready = 0;
	sdl->is_init = 0;
	get_champ_name(sdl);
	return (sdl);
}
