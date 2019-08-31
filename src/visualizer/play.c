#include "../../include/visualizer.h"



SDL_Color	get_color_of(char *champ, t_sdl *sdl)
{
	int		i;

	i = -1;
	while (sdl->selected_cmp[++i].text)
	{
		if (strcmp(sdl->selected_cmp[i].text, champ) == 0)
		{
			sdl->score[i] += 1;
			return (sdl->selected_cmp[i].color);
		}
	}
	return (C_WH);
}

void	color_adjust(SDL_Color *color, double percent)
{
	color->r *= percent;
	color->g *= percent;
	color->b *= percent;
}

void	render_empty_map(t_sdl *sdl)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= 64)
	{
		x = -1;
		while (++x <= 64)
		{
			SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
			SDL_RenderFillRect(sdl->ren, &(SDL_Rect){
				MAP_P_X + x * BOX_W + 1, MAP_P_Y + y * BOX_H + 1,
				BOX_W - 2, BOX_H - 2});
		}
	}
}

/*
** https://discourse.libsdl.org/t/sdl2-ttf-text-rendering-slow-how-to-make-faster/21068/4
** I think it slow because of the Freetype 2 which is used
** internally by SDL_ttf. TrueType processing is quite complicated
** and it takes time to compute. The best way of using SDL_ttf
** would be to create a new texture only when text changes (caching).
** Anyway try profiling the code. It probably somewhere else :).
*/
void	render_instruction(t_sdl *sdl, t_mem *mem)
{
	char	*tmp;
	if (mem->text)
	{
		tmp = base_itoa((unsigned char)mem->data, 16, 2);
		if (strcmp(tmp, mem->text) != 0)
		{
			free(mem->text);
			mem->text = tmp;
			SDL_DestroyTexture(mem->tex);
		}
	}
	else
		mem->text = base_itoa((unsigned char)mem->data, 16, 2);
	sdl->scr = TTF_RenderText_Solid(sdl->font[1], mem->text, C_BK);
	mem->tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
	SDL_RenderCopy(sdl->ren, mem->tex, NULL, &(mem->rect));
}

void	render_map(t_sdl *sdl)
{
	int			i;
	SDL_Color	color;
	t_mem		*tmp;

	i = -1;
	tmp = sdl->mem_start;
	while (++i < MEM_SIZE)
	{
		if (tmp->owner)
			color = get_color_of(tmp->owner, sdl);
		else
			color = C_WH;
		if (tmp->is_pc)
			color_adjust(&color, 0.5);
		else if (tmp->is_instruction)
			color_adjust(&color, 0.85);
		SDL_SetRenderDrawColor(sdl->ren, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(sdl->ren, &tmp->rect);
		if (sdl->in_show && tmp->is_instruction)
			render_instruction(sdl, tmp);
		else if (!sdl->in_show && tmp->text)
		{
			free(tmp->text);
			tmp->text = NULL;
			SDL_DestroyTexture(tmp->tex);
		}
		tmp = tmp->next;
	}
}

void	render_status_bar(t_sdl *sdl)
{
	int			size;
	int			pos;
	int			i;
	int			total;
	SDL_Color	c;

	pos = MAP_P_X;
	i = -1;
	total = 0;
	while (++i < sdl->nb_of_p)
		total += sdl->score[i];
	i = -1;
	while (++i < sdl->nb_of_p)
	{
		size = ((sdl->score[i] * (MAP_SIZE_X - 50))/ total);
		c = sdl->selected_cmp[i].color;
		SDL_SetRenderDrawColor(sdl->ren, c.r, c.g, c.b, 255);
		SDL_RenderFillRect(sdl->ren, &(SDL_Rect){pos, 25, size, 20});
		sdl->score[i] = 0;
		pos += size;
	}
}

void	render_finish(t_sdl *sdl)
{
	t_set	set;

	set = sdl->selected_cmp[sdl->winner];
	SDL_SetRenderDrawColor(sdl->ren, C_WH.r, C_WH.g, C_WH.b, A);
	SDL_RenderFillRect(sdl->ren,
		&(SDL_Rect){MAP_P_X - 40, 580, MAP_SIZE_X + 40, 440});
	SDL_SetRenderDrawColor(sdl->ren, R * 0.75, G * 0.75, B * 0.75, A);
	SDL_RenderFillRect(sdl->ren,
		&(SDL_Rect){MAP_P_X - 20, 600, MAP_SIZE_X, 400});
	render_only_name(sdl, set.text, NULL);
	sdl->tex[5] = SDL_CreateTextureFromSurface(sdl->ren, sdl->scr);
	SDL_RenderCopy(sdl->ren, sdl->tex[5], NULL, &((SDL_Rect){
		MAP_P_X + 20, 600 + 20, MAP_SIZE_X - 40 , 400 - 40
	}));
}

void	render_cycle_box(t_sdl *sdl, int cycle)
{
	int			x;

	x = -1;
	while (++x < 15)
	{
		SDL_SetRenderDrawColor(sdl->ren, C_P1.r + 13 * x,
			C_P1.g + 5 * x, C_P1.b - 9 * x, 255);
		SDL_RenderFillRect(sdl->ren, &(SDL_Rect){0, 1320 - (x * 90), 80, 85});
		if (cycle / CHUNK == x)
		{
			SDL_SetRenderDrawColor(sdl->ren, C_BK.r, C_BK.g, C_BK.b, 255);
			SDL_RenderFillRect(sdl-> ren, &(SDL_Rect){
				0, 1320 - (x * 90), 20, 85});
			cycle -= cycle > CHUNK ? CHUNK * x : 0;
		}
	}
	while (cycle > 0)
	{
		x = cycle / CHUNK;
		SDL_SetRenderDrawColor(sdl->ren, C_P1.r + 13 * x,
			C_P1.g + 5 * x, C_P1.b - 9 * x, 255);
		SDL_RenderFillRect(sdl->ren, &(SDL_Rect){
			2460, 1390 - ((cycle / 100) * 13), 60, 8});
		cycle -= 100;
	}
}