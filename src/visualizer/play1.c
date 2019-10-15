/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 03:08:54 by hnam              #+#    #+#             */
/*   Updated: 2019/09/27 16:35:04 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/visualizer.h"

t_set		g_play_sets[] =
{
	{"Player 1", (SDL_Rect){130, 1470, 300, 60}, C_GREY},
	{"Player 2", (SDL_Rect){440, 1470, 300, 60}, C_GREY},
	{"Player 3", (SDL_Rect){750, 1470, 300, 60}, C_GREY},
	{"Player 4", (SDL_Rect){1060, 1470, 300, 60}, C_GREY},
	{"Player 1", (SDL_Rect){130, 1440, 300, 30}, C_P1},
	{"Player 2", (SDL_Rect){440, 1440, 300, 30}, C_P2},
	{"Player 3", (SDL_Rect){750, 1440, 300, 30}, C_P3},
	{"Player 4", (SDL_Rect){1060, 1440, 300, 30}, C_P4},
};

t_set		g_play_text[] =
{
	{"COREWAR", (SDL_Rect){1820, 1410, 600, 100}, C_BL},
	{"aderby, drosa-ta, nwhitlow, hnam",
		(SDL_Rect){1820, 1530, 20 * 29, 20}, C_BL},
	{"UP INSTRUCTION", (SDL_Rect){1500, 1440, 270, 30}, C_BK},
	{"DOWN VISUALIZE", (SDL_Rect){1500, 1475, 270, 30}, C_BK},
	{"ESC QUIT ", (SDL_Rect){1500, 1510, 200, 30}, C_BK},
};

void		render_play_page(t_sdl *sdl)
{
	static int	first = 0;
	int			i;

	render_map(sdl);
	render_status_bar(sdl);
	render_play_box(sdl);
	if (first++ == 0)
		render_play_text(sdl);
	i = -1;
	while (++i < sdl->nb_of_p)
		SDL_RenderCopy(sdl->ren, sdl->champ_tex[i],
			NULL, &(sdl->champ_rect[i]));
	i = -1;
	while (++i < 5)
		SDL_RenderCopy(sdl->ren, sdl->tex[i], NULL, &(sdl->rect[i]));
}

void		render_play_box(t_sdl *sdl)
{
	t_set	set;
	int		idx;

	idx = -1;
	while (++idx < 8)
	{
		if (!sdl->selected_cmp[idx % 4].text)
			continue ;
		set = g_play_sets[idx];
		SDL_SetRenderDrawColor(sdl->ren, R, G, B, A);
		SDL_RenderFillRect(sdl->ren, &(set.rect));
	}
}

void		render_play_text(t_sdl *sdl)
{
	int		i;
	t_set	set;

	i = -1;
	while (++i < sdl->nb_of_p)
	{
		set = g_play_sets[i];
		set.rect.x += 5;
		set.rect.y += 5;
		set.rect.h -= 10;
		set.rect.w -= 10;
		sdl->champ_rect[i] = set.rect;
		render_only_name(sdl, sdl->selected_cmp[i].text, NULL);
		sdl->champ_tex[i] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
		SDL_FreeSurface(sdl->scr);
	}
	i = -1;
	while (++i < 5)
	{
		set = g_play_text[i];
		sdl->rect[i] = set.rect;
		sdl->scr = TTF_RenderText_Solid(sdl->font[0], set.text, set.color);
		sdl->tex[i] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
		SDL_FreeSurface(sdl->scr);
	}
}

SDL_Color	get_color_of(char *champ, t_sdl *sdl)
{
	int		i;

	i = -1;
	while (sdl->selected_cmp[++i].text)
	{
		if (ft_strcmp(sdl->selected_cmp[i].text, champ) == 0)
		{
			sdl->score[i] += 1;
			return (sdl->selected_cmp[i].color);
		}
	}
	return (C_WH);
}

void		color_adjust(SDL_Color *color, double percent)
{
	color->r *= percent;
	color->g *= percent;
	color->b *= percent;
}
