/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 03:27:18 by hnam              #+#    #+#             */
/*   Updated: 2019/09/24 17:25:24 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/visualizer.h"

t_set	g_start_sets[] =
{
	{"CHAMP_BOX", (SDL_Rect){150, 530, 630, 840}, C_GREY},
	{"START", (SDL_Rect){1580, 1280, 340, 120}, C_BL},
	{"Player 1", (SDL_Rect){1100, 600, 450, 50}, C_P1},
	{"Player 2", (SDL_Rect){1900, 600, 450, 50}, C_P2},
	{"Player 3", (SDL_Rect){1100, 1000, 450, 50}, C_P3},
	{"Player 4", (SDL_Rect){1900, 1000, 450, 50}, C_P4},
	{"Player 1", (SDL_Rect){1100, 650, 450, 100}, C_GREY},
	{"Player 2", (SDL_Rect){1900, 650, 450, 100}, C_GREY},
	{"Player 3", (SDL_Rect){1100, 1050, 450, 100}, C_GREY},
	{"Player 4", (SDL_Rect){1900, 1050, 450, 100}, C_GREY},
};

void	render_start_page(t_sdl *sdl)
{
	int			idx;
	static int	is_first = 0;

	render_start_box(sdl);
	if (is_first++ == 0)
	{
		render_champs(sdl);
		render_start_text(sdl);
	}
	idx = -1;
	while (++idx < NUM_OF_CHAMP)
		SDL_RenderCopy(sdl->ren, sdl->champ_tex[idx],
			NULL, &(sdl->champ_rect[idx]));
	idx = -1;
	while (++idx < NUM_OF_INFO)
		SDL_RenderCopy(sdl->ren, sdl->tex[idx], NULL, &(sdl->rect[idx]));
}

void	render_champs(t_sdl *sdl)
{
	int		idx;
	int		len;

	idx = -1;
	while (++idx < NUM_OF_CHAMP && sdl->champs[sdl->page * 10 + idx])
		sdl->curr_champs[idx] = sdl->champs[sdl->page * 10 + idx];
	while (idx < NUM_OF_CHAMP)
		sdl->curr_champs[idx++] = NULL;
	idx = -1;
	while (++idx < 10)
	{
		if (sdl->curr_champs[idx])
		{
			len = get_small(520, 30 * ft_strlen(sdl->curr_champs[idx]));
			sdl->champ_rect[idx] = (SDL_Rect){260, 570 + idx * 80, len, 40};
			render_only_name(sdl, sdl->curr_champs[idx], &sdl->champ_rect[idx]);
		}
		else
		{
			sdl->champ_rect[idx] = (SDL_Rect){260, 570 + idx * 80, 0, 40};
			sdl->scr = NULL;
		}
		sdl->champ_tex[idx] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
		SDL_FreeSurface(sdl->scr);
	}
}

int		render_start_box(t_sdl *sdl)
{
	t_set		set;
	int			idx;

	idx = -1;
	while (++idx < 10)
	{
		set = g_start_sets[idx];
		if (ft_strcmp(set.text, "START") == 0 && sdl->nb_of_p < 1)
			set.color = C_GREY;
		SDL_SetRenderDrawColor(sdl->ren, R, G, B, A);
		SDL_RenderFillRect(sdl->ren, &(set.rect));
	}
	idx = -1;
	while (++idx < 10)
	{
		SDL_SetRenderDrawColor(sdl->ren, C_BL.r, C_BL.g, C_BL.b, C_BL.a);
		SDL_RenderFillRect(sdl->ren, &(SDL_Rect){185, 575 + 80 * idx, 30, 30});
	}
	return (0);
}

int		is_existed(t_sdl *sdl, char *clicked)
{
	int	i;

	i = -1;
	while (++i < sdl->nb_of_p)
		if (ft_strcmp(sdl->selected_cmp[i].text, clicked) == 0)
			return (1);
	return (0);
}
