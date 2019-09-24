/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:02:27 by hnam              #+#    #+#             */
/*   Updated: 2019/09/02 17:22:06 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/visualizer.h"

int		is_clicked(t_sdl *sdl, SDL_Rect btn)
{
	if ((BTN_X >= btn.x && BTN_X <= btn.x + btn.w) &&
		(BTN_Y >= btn.y && BTN_Y <= btn.y + btn.h))
		return (1);
	return (0);
}

void	event_handler(t_sdl *sdl)
{
	if (sdl->e.type == SDL_QUIT)
		sdl->is_quit = 1;
	if (sdl->e.type == SDL_QUIT || sdl->e.key.keysym.sym == SDLK_ESCAPE)
		sdl->is_running = 0;
	if (sdl->ready == 0 && sdl->e.type == SDL_MOUSEBUTTONDOWN)
	{
		select_player(sdl);
		unselect_player(sdl);
		change_page(sdl);
		sdl->ready = (is_clicked(sdl, (SDL_Rect){1610, 1300, 300, 80})
			&& (sdl->nb_of_p > 0));
		sdl->ready ? destroy_start_page(sdl) : 0;
	}
	if (KEY == SDLK_UP)
		sdl->in_show = 1;
	if (KEY == SDLK_DOWN)
		sdl->in_show = 0;
}

void	end_process(t_sdl *sdl)
{
	int		i;

	i = -1;
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	while (++i < 5)
		SDL_DestroyTexture(sdl->tex[i]);
	if (sdl->mem_start->text)
	{
		while (i++ < MEM_SIZE + 5)
		{
			free(sdl->mem_start->text);
			SDL_DestroyTexture(sdl->mem_start->tex);
			sdl->mem_start = sdl->mem_start->next;
		}
	}
	while (sdl->is_init && --sdl->nb_of_p >= 0)
		free(sdl->selected_cmp[sdl->nb_of_p].text);
	free_char_pp(sdl->champs);
	TTF_CloseFont(sdl->font[0]);
	TTF_CloseFont(sdl->font[1]);
	TTF_Quit();
	SDL_Quit();
	free(sdl);
}

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
	sdl->scr = TTF_RenderText_Solid(sdl->font[0], tmp[0], C_BK);
	if (rect)
	{
		if ((len = ft_strlen(tmp[0]) * 40) > 520)
			len = 520;
		rect->w = len;
	}
	free_char_pp(tmp);
	free_char_pp(path);
}

void	free_char_pp(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
