#include "visualizer.h"

t_set	g_play_sets[] =
{
	{"Player 1", (SDL_Rect){256, 1320, 300, 80}, C_GREY},
	{"Player 2", (SDL_Rect){600, 1320, 300, 80}, C_GREY},
	{"Player 3", (SDL_Rect){256, 1470, 300, 80}, C_GREY},
	{"Player 4", (SDL_Rect){600, 1470, 300, 80}, C_GREY},
	{"Player 1", (SDL_Rect){256, 1280, 300, 40}, C_P1},
	{"Player 2", (SDL_Rect){600, 1280, 300, 40}, C_P2},
	{"Player 3", (SDL_Rect){256, 1430, 300, 40}, C_P3},
	{"Player 4", (SDL_Rect){600, 1430, 300, 40}, C_P4},
};

t_set	g_play_text[] =
{

};

void	render_play_page(t_sdl *sdl)
{
	static int	first = 0;
	int			i;

	render_map(sdl, 64, 64);
	render_play_box(sdl);
	if (first++ == 0)
	{
		render_play_text(sdl);
	}
	i = -1;
	while (++i < sdl->nb_of_p)
		SDL_RenderCopy(sdl->ren, sdl->champ_tex[i],
			NULL, &(sdl->champ_rect[i]));

}

void	render_play_box(t_sdl *sdl)
{
	t_set		set;
	int			idx;

	idx = -1;
	while (++idx < 8)
	{
		set = g_play_sets[idx];
		SDL_SetRenderDrawColor(sdl->ren, R, G, B, A);
		SDL_RenderFillRect(sdl->ren, &(set.rect));
	}
}

	// if (sdl->curr_champs[idx])
	// 	{
	// 		if ((len = 40 * ft_strlen(sdl->curr_champs[idx])) > 520)
	// 			len = 520;
	// 		sdl->champ_rect[idx] = (SDL_Rect){260, 570 + idx * 80, len, 40};
	// 	}
	// 	else
	// 		sdl->champ_rect[idx] = (SDL_Rect){260, 570 + idx * 80, 0, 40};
	// 	sdl->scr = TTF_RenderText_Solid(sdl->font[0], sdl->curr_champs[idx], C_BK);
	// 	sdl->champ_tex[idx] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);

void	render_play_text(t_sdl *sdl)
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
		sdl->scr = TTF_RenderText_Solid(sdl->font[1], sdl->selected_cmp[i], C_BK);
		sdl->champ_tex[i] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
	}
}

