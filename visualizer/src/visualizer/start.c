#include "visualizer.h"

int	is_clicked(t_sdl *sdl, SDL_Rect btn)
{
	printf("x = (%d~%d) \t y = (%d ~ %d)\n", btn.x, btn.x + btn.w, btn.y, btn.y + btn.h);
	if ((BTN_X >= btn.x && BTN_X <= btn.x + btn.w) &&
		(BTN_Y >= btn.y && BTN_Y <= btn.y + btn.h))
			sdl->cmp_selected = 1;
	return (0);
}

int	render_start_text(t_sdl *sdl)
{
	int i;

	sdl->rect[0] = (SDL_Rect){530, 20, 1500, 300};
	get_text_and_rect("COREWAR", sdl, 0, (SDL_Color){0, 0, 0, 255});
	sdl->rect[1] = (SDL_Rect){260, 420, 200, 50};
	get_text_and_rect("CHAMPS", sdl, 1, (SDL_Color){0, 0, 0, 255});
	sdl->rect[2] = (SDL_Rect){1600, 1400, 300, 80};
	get_text_and_rect("START", sdl,2, (SDL_Color){0, 0, 0, 255});
	i = -1;
	while (++i < 3)
		SDL_RenderCopy(sdl->ren, sdl->tex[i], NULL, &(sdl->rect[i]));
	return (0);
}

int	render_start_btn(t_sdl *sdl, t_btn *btn)
{
	SDL_SetRenderDrawColor(sdl->ren, 200, 100, 20, 255);
	SDL_RenderFillRect(sdl->ren, &(btn->start));
	return (0);
}
