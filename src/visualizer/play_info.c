#include "../../include/visualizer.h"

t_set	g_play_sets[] =
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

t_set	g_play_text[] =
{
	{"COREWAR", (SDL_Rect){1820, 1410, 600, 100}, C_BL},
	{"aderby, drosa-ta, nwhitlow, hnam", (SDL_Rect){1820, 1530, 20 * 29, 20}, C_BL},
	{"UP INSTRUCTION", (SDL_Rect){1500, 1440, 300, 35}, C_BK},
	{"DOWN ONLY VISU", (SDL_Rect){1500, 1480, 200, 35}, C_BK},
	{"ESC QUIT ", (SDL_Rect){1500, 1520, 200, 35}, C_BK},
};

void	render_only_name(t_sdl *sdl, char *text, SDL_Rect *rect)
{
	char	**path;
	char	**tmp;
	int		k;
	int		len;

	k = 0;
	if (!text)
		return ;
	path = ft_strsplit(text, '/');
	while (path[k] && path[k + 1])
		k++;
	tmp = ft_strsplit(path[k], '.');
	sdl->scr = TTF_RenderText_Solid(sdl->font[1], tmp[0], C_BK);
	if (rect)
		rect->w = ((len = ft_strlen(tmp[0]) * 40) > 520) ? 520 : len;
	free_char_pp(tmp);
	free_char_pp(path);
}

void	render_play_page(t_sdl *sdl)
{
	static int	first = 0;
	int			i;

	render_map(sdl);
	// render_empty_map(sdl);
	render_status_bar(sdl);
	render_play_box(sdl);
	if (first++ == 0)
	{
		render_play_text(sdl);
	}
	i = -1;
	while (++i < sdl->nb_of_p)
		SDL_RenderCopy(sdl->ren, sdl->champ_tex[i],
			NULL, &(sdl->champ_rect[i]));
	i = -1;
	while (++i < 5)
		SDL_RenderCopy(sdl->ren, sdl->tex[i], NULL, &(sdl->rect[i]));

}

void	render_play_box(t_sdl *sdl)
{
	t_set		set;
	int			idx;

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
		// get name!
		// sdl->scr = TTF_RenderText_Solid(sdl->font[1], sdl->champ_name[i], C_BK);
		render_only_name(sdl, sdl->selected_cmp[i].text, NULL);
		sdl->champ_tex[i] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
	}
	i = -1;
	while (++i < 5)
	{
		set = g_play_text[i];
		sdl->rect[i] = set.rect;
		sdl->scr = TTF_RenderText_Solid(sdl->font[1], set.text, set.color);
		sdl->tex[i] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
	}
}

