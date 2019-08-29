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
		// tmp->rect = (SDL_Rect){MAP_P_X + (i % 64) * BOX_W + 1,
		// MAP_P_Y + (i  / 64) * BOX_H + 1, BOX_W - 2, BOX_H - 2};
		SDL_RenderFillRect(sdl->ren, &tmp->rect);
		if (sdl->in_show && tmp->is_instruction)
			render_instruction(sdl, tmp);
		// else if (sdl->in_show == 0 && time > 0 && tmp->text)
		// {
		// 	free(tmp->text);
		// 	SDL_DestroyTexture(tmp->tex);
		// }

		tmp = tmp->next;
	}
	// if (sdl->in_show)
	// 	time++;
	// if (sdl->in_show == 0 && time > 0)
	// {
	// 	tmp = sdl->mem_start;
	// 	while (tmp)
	// 	{
	// 		free(mem->text);
	// 		SDL_DestroyTexture(mem->tex);
	// 		tmp = tmp->next
	// 	}
	// }
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


// void	render_map(t_sdl *sdl, int size_x, int size_y)
// {
// 	static int	i = 0;
// 	static int	s = 0;
// 	static int	j = 0;
// 	int	BOX_W;
// 	int	BOX_H;
// 	int	x;
// 	int	y;

// 	BOX_W = MAP_SIZE_X / size_x;
// 	BOX_H = MAP_SIZE_Y / size_y;
// 	y = -1;
// 	if (i++ > 64)
// 	{
// 		i %= 64;
// 		s += 1;
// 	}
// 	if (sdl->is_forked && j++ > 64)
// 	{
// 		j %= 64;
// 		s += 1;
// 	}
// 	while (++y < size_y)
// 	{
// 		x = -1;
// 		while (++x < size_x)
// 		{
// 			// if (x < 10 && y < 10)
// 			// {
// 				// printf("(%d * %d + %d)%d  == %d\n", y, x, x, y * x + x, i);
// 				if (y * size_x + x <= s)
// 				{
// 					if (y * size_x + x == i || (sdl->is_forked && y * size_x + x == j))
// 					{
// 						SDL_SetRenderDrawColor(sdl->ren, 50, 155, 80, 255);
// 						printf("drawing x : %d\t y : %d\n", x, y);
// 					}
// 					else
// 						SDL_SetRenderDrawColor(sdl->ren, 10, 115, 40, 255);
// 				}

// 				else if (y * size_x + x == i || (sdl->is_forked && y * size_x + x == j))
// 					SDL_SetRenderDrawColor(sdl->ren, 10, 10, 10, 255);
// 				else
// 					SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
// 				SDL_RenderFillRect(sdl->ren, &(SDL_Rect){
// 					MAP_P_X + x * BOX_W + 1, MAP_P_Y + y * BOX_H + 1,
// 					BOX_W - 2, BOX_H - 2});
// 			// }
// 		}
// 	}
// }
