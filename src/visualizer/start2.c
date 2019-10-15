/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 03:12:47 by hnam              #+#    #+#             */
/*   Updated: 2019/09/24 17:15:17 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/visualizer.h"

t_set	g_text_sets[] =
{
	{"COREWAR", (SDL_Rect){530, 20, 1500, 300}, C_BL},
	{"CHAMPS", (SDL_Rect){260, 420, 300, 50}, C_BK},
	{"START", (SDL_Rect){1610, 1300, 300, 80}, C_BK},
	{"Player 1", (SDL_Rect){1150, 520, 350, 60}, C_BK},
	{"Player 2", (SDL_Rect){1950, 520, 350, 60}, C_BK},
	{"Player 3", (SDL_Rect){1150, 920, 350, 60}, C_BK},
	{"Player 4", (SDL_Rect){1950, 920, 350, 60}, C_BK},
	{NULL, (SDL_Rect){1130, 660, 400, 80}, C_BK},
	{NULL, (SDL_Rect){1930, 660, 400, 80}, C_BK},
	{NULL, (SDL_Rect){1130, 1060, 400, 80}, C_BK},
	{NULL, (SDL_Rect){1930, 1060, 400, 80}, C_BK},
	{"PREV", (SDL_Rect){260, 1430, 120, 30}, C_BK},
	{"NEXT", (SDL_Rect){450, 1430, 120, 30}, C_BK},
	{"aderby, drosa-ta, nwhitlow, hnam",
		(SDL_Rect){1700, 300, 20 * 29, 20}, C_BL},
};

int		render_start_text(t_sdl *sdl)
{
	int		idx;
	t_set	set;

	idx = -1;
	while (++idx < NUM_OF_INFO)
	{
		set = g_text_sets[idx];
		if (set.text && ft_strcmp(set.text, "START") == 0 && sdl->nb_of_p > 0)
			set.color = C_WH;
		sdl->rect[idx] = set.rect;
		if (idx >= 7 && idx <= 10 && set.text)
			render_only_name(sdl, set.text, NULL);
		else
			sdl->scr = TTF_RenderText_Solid(sdl->font[0], set.text, set.color);
		sdl->tex[idx] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
		SDL_FreeSurface(sdl->scr);
	}
	return (0);
}

/*
** event handler by click to select or unselect
*/

void	select_player(t_sdl *sdl)
{
	int	idx;

	idx = 0;
	if (!is_clicked(sdl, (SDL_Rect){120, 500, 660, 900}))
		return ;
	while (sdl->nb_of_p < 4 && idx < NUM_OF_CHAMP &&
		sdl->curr_champs[idx])
	{
		if (is_clicked(sdl, sdl->champ_rect[idx])
			&& !is_existed(sdl, sdl->curr_champs[idx]))
		{
			sdl->selected_cmp[sdl->nb_of_p].text =
				sdl->curr_champs[idx];
			g_text_sets[7 + sdl->nb_of_p].text =
				sdl->curr_champs[idx];
			sdl->nb_of_p += 1;
			destroy_start_page(sdl);
			render_champs(sdl);
			render_start_text(sdl);
			return ;
		}
		idx++;
	}
}

void	unselect_player(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < 4 && !is_clicked(sdl, g_text_sets[7 + i].rect))
		i++;
	if (i == 4)
		return ;
	sdl->nb_of_p -= (sdl->nb_of_p != 0);
	sdl->selected_cmp[i].text = NULL;
	g_text_sets[7 + i].text = NULL;
	while (i < sdl->nb_of_p)
	{
		sdl->selected_cmp[i].text = sdl->selected_cmp[i + 1].text;
		sdl->selected_cmp[i + 1].text = NULL;
		g_text_sets[7 + i].text = g_text_sets[7 + i + 1].text;
		g_text_sets[7 + i + 1].text = NULL;
		i++;
	}
	destroy_start_page(sdl);
	render_champs(sdl);
	render_start_text(sdl);
}

void	change_page(t_sdl *sdl)
{
	int	changed;

	changed = 0;
	if (is_clicked(sdl, (SDL_Rect){260, 1430, 120, 30})
		&& sdl->page > 0 && (changed = 1))
		sdl->page -= 1;
	if (is_clicked(sdl, (SDL_Rect){450, 1430, 120, 30})
		&& sdl->page < 5 && (changed = 1))
		sdl->page += 1;
	if (!changed)
		return ;
	destroy_start_page(sdl);
	render_champs(sdl);
	render_start_text(sdl);
}

/*
** when start page useless, need to free texture
*/

void	destroy_start_page(t_sdl *sdl)
{
	int	idx;

	idx = -1;
	while (++idx < NUM_OF_INFO)
		SDL_DestroyTexture(sdl->tex[idx]);
	idx = -1;
	while (++idx < NUM_OF_CHAMP)
		SDL_DestroyTexture(sdl->champ_tex[idx]);
}
