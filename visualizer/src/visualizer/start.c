#include "visualizer.h"

t_set	g_start_sets[] =
{
	{"CHAMP_BOX", (SDL_Rect){80, 500, 660, 1000}, C_WH},
	{"CHAMPS", (SDL_Rect){240, 400, 240, 90}, C_WH},
	{"START", (SDL_Rect){1580, 1380, 340, 120}, C_ORG},
	{"Player 1", (SDL_Rect){1100, 500, 350, 50}, C_ORG},
	{"Player 2", (SDL_Rect){1900, 500, 350, 50}, C_ORG},
	{"Player 3", (SDL_Rect){1100, 900, 350, 50}, C_ORG},
	{"Player 4", (SDL_Rect){1900, 900, 350, 50}, C_ORG},
	{"Player 1", (SDL_Rect){1100, 550, 350, 100}, C_WH},
	{"Player 2", (SDL_Rect){1900, 550, 350, 100}, C_WH},
	{"Player 3", (SDL_Rect){1100, 950, 350, 100}, C_WH},
	{"Player 4", (SDL_Rect){1900, 950, 350, 100}, C_WH},
	{"zork", (SDL_Rect){180, 570, 40, 40}, C_ORG},
	{"turtle", (SDL_Rect){180, 640, 40, 40}, C_ORG},
	{"helltrain", (SDL_Rect){180, 710, 40, 40}, C_ORG},
	{"fluttershy", (SDL_Rect){180, 780, 40, 40}, C_ORG},
	{"bigzork", (SDL_Rect){180, 850, 40, 40}, C_ORG},
	{"bee_gees", (SDL_Rect){180, 920, 40, 40}, C_ORG},
};

t_set	g_champ_sets[] =
{
	{"zork", (SDL_Rect){180, 570, 40 * 5, 40}, C_BK},
	{"turtle", (SDL_Rect){180, 640, 40 * 8, 40}, C_BK},
	{"helltrain", (SDL_Rect){180, 710, 40 * 11, 40}, C_BK},
	{"fluttershy", (SDL_Rect){180, 780, 40 * 12, 40}, C_BK},
	{"bigzork", (SDL_Rect){180, 850, 40 * 9, 40}, C_BK},
	{"bee_gees", (SDL_Rect){180, 920, 40 * 10, 40}, C_BK},
	{NULL, (SDL_Rect){0, 0, 0, 0}, C_BK}
};

t_set	g_text_sets[] =
{
	{"COREWAR", (SDL_Rect){530, 20, 1500, 300}, C_BK},
	{"CHAMPS", (SDL_Rect){230, 420, 300, 50}, C_BK},
	{"START", (SDL_Rect){1600, 1400, 300, 80}, C_BK},
	{"Player 1", (SDL_Rect){1100, 420, 350, 60}, C_BK},
	{"Player 2", (SDL_Rect){1900, 420, 350, 60}, C_BK},
	{"Player 3", (SDL_Rect){1100, 820, 350, 60}, C_BK},
	{"Player 4", (SDL_Rect){1900, 820, 350, 60}, C_BK},
	{"zork", (SDL_Rect){260, 570, 40 * 3, 40}, C_BK},
	{"turtle", (SDL_Rect){260, 640, 40 * 6, 40}, C_BK},
	{"helltrain", (SDL_Rect){260, 710, 40 * 9, 40}, C_BK},
	{"fluttershy", (SDL_Rect){260, 780, 40 * 10, 40}, C_BK},
	{"bigzork", (SDL_Rect){260, 850, 40 * 7, 40}, C_BK},
	{"bee_gees", (SDL_Rect){260, 920, 40 * 8, 40}, C_BK},
	{"", (SDL_Rect){1100, 550, 350, 100}, C_BK},
	{"", (SDL_Rect){1900, 550, 350, 100}, C_BK},
	{"", (SDL_Rect){1100, 950, 350, 100}, C_BK},
	{"", (SDL_Rect){1900, 950, 350, 100}, C_BK},
};

void	render_text(t_sdl *sdl, int idx)
{
	t_set	set;

	set = g_text_sets[idx];
	sdl->rect[idx] = set.rect;
	sdl->scr = TTF_RenderText_Solid(sdl->font[0], set.text, set.color);
	sdl->tex[idx] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
}


int	is_clicked(t_sdl *sdl, SDL_Rect btn)
{
	if ((BTN_X >= btn.x && BTN_X <= btn.x + btn.w) &&
		(BTN_Y >= btn.y && BTN_Y <= btn.y + btn.h))
		return (1);
	return (0);
}

int		is_existed(t_sdl *sdl, t_set set)
{
	int	i;

	i = -1;
	while (++i < sdl->nb_of_p)
		if (ft_strcmp(sdl->selected_cmp[i].text, set.text) == 0)
			return (1);
	return (0);
}

void	select_player(t_sdl *sdl)
{
	int	i;

	i = -1;
	while (sdl->nb_of_p < 4 && g_champ_sets[++i].text)
	{
		if (is_clicked(sdl, g_champ_sets[i].rect) && !is_existed(sdl, g_champ_sets[i]))
		{
			sdl->selected_cmp[sdl->nb_of_p] = g_champ_sets[i];
			g_text_sets[13 + sdl->nb_of_p++].text = ft_strdup( g_champ_sets[i].text);
			printf("select %s\n", sdl->selected_cmp[sdl->nb_of_p - 1].text);
			// memcpy(sdl->selected_cmp[sdl->nb_of_p++], &g_champ_sets[i], sizeof(t_set));
//
			// break ;
		}
	}

}

int	render_start_text(t_sdl *sdl)
{
	int i;

	i = -1;
	while (++i < 17)
		render_text(sdl, i);
	i = -1;
	while (sdl->tex[++i])
		SDL_RenderCopy(sdl->ren, sdl->tex[i], NULL, &(sdl->rect[i]));
	return (0);
}

int	render_start_btn(t_sdl *sdl, t_btn *btn)
{
	SDL_SetRenderDrawColor(sdl->ren, 200, 100, 20, 255);
	SDL_RenderFillRect(sdl->ren, &(btn->start));
	return (0);
}

int	render_start_box(t_sdl *sdl)
{
	t_set		set;
	int			idx;

	idx = 0;
	while (idx < 17)
	{
		set = g_start_sets[idx];
		SDL_SetRenderDrawColor(sdl->ren, R, G, B, A);
		SDL_RenderFillRect(sdl->ren, &(set.rect));
		idx++;
	}
	return (0);
}
