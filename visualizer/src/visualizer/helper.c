/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:02:27 by hnam              #+#    #+#             */
/*   Updated: 2019/08/13 21:59:53 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_score(t_f *f)
{
	int	y;
	int	x;

	y = -1;
	f->s_p1 = 0;
	f->s_p2 = 0;
	while (f->m[++y])
	{
		x = -1;
		while (f->m[y][++x])
		{
			if (ft_strchr(f->p1, f->m[y][x]))
				f->s_p1 += 1;
			else if (ft_strchr(f->p2, f->m[y][x]))
				f->s_p2 += 1;
		}
	}
}

void	get_color_by(char p, t_f *f, t_sdl *sdl)
{
	SDL_Color	cl;

	cl = ft_strchr(f->p1, p) ? f->c_p1 : f->c_p2;
	if (p >= 'o' && p <= 'z')
	{
		cl.r *= 0.8;
		cl.g *= 0.8;
		cl.b *= 0.8;
	}
	SDL_SetRenderDrawColor(sdl->ren, cl.r, cl.g, cl.b, cl.a);
}

void	event_handler(t_sdl *sdl, t_btn *btn)
{
	if (sdl->e.type == SDL_QUIT)
		sdl->is_quit = 1;
	if (sdl->e.type == SDL_QUIT || sdl->e.key.keysym.sym == SDLK_ESCAPE)
		sdl->is_running = 0;
	if (sdl->e.type == SDL_MOUSEBUTTONDOWN)
		is_clicked(sdl, btn->start);

	//
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
