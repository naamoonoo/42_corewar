/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:01:44 by hnam              #+#    #+#             */
/*   Updated: 2019/08/16 22:05:37 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


void	main_loop(t_sdl *sdl, t_btn *btn)
{
	while (sdl->is_running)
	{
		while (SDL_PollEvent(&(sdl->e)))
			event_handler(sdl, btn);
		SDL_RenderClear(sdl->ren);
		if (sdl->ready_to_start)
		{
			render_map(sdl, 64, 64);
		}
		else
		{
			for (int i = 0; i < sdl->nb_of_p; i++)
			{
				printf("[%d]%s\n", i, sdl->selected_cmp[i].text);
			}
			render_start_box(sdl);
			// render_start_btn(sdl, btn);
			render_start_text(sdl);
		}
		SDL_SetRenderDrawColor(sdl->ren, 0xdc, 0xdd, 0xe1, 0);
		SDL_RenderPresent(sdl->ren);
		SDL_Delay(1000 / 60);
	}
}

int		main(int ac, char *av[])
{
	t_sdl	*sdl;
	t_btn	*btn;

	(void)av[ac - 1];

	/*
	** if args come in play right away with that champs
	** if not show the selection page to start
	** if (ac != 2 && FP("./visualizer [trace]\n"))
	** 	return (0);
	*/

	sdl = sdl_init();
	btn = btn_init();
	main_loop(sdl, btn);
	while (!sdl->is_quit)
	{
		while (SDL_PollEvent(&(sdl->e)))
			if (sdl->e.type == SDL_QUIT || sdl->e.key.keysym.sym == 27)
				sdl->is_quit = 1;
		SDL_Delay(1000 / 60);
	}
	end_process(sdl);
	return (0);
}
