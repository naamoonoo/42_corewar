#include "visualizer.h"


void	render_map(t_sdl *sdl, int size_x, int size_y)
{
	static int	i = 0;
	static int	s = 0;
	static int	j = 0;
	int	width;
	int	height;
	int	x;
	int	y;

	width = MAP_SIZE_X / size_x;
	height = MAP_SIZE_Y / size_y;
	y = -1;
	if (i++ > 64)
	{
		i %= 64;
		s += 1;
	}
	if (sdl->is_forked && j++ > 64)
	{
		j %= 64;
		s += 1;
	}
	while (++y < size_y)
	{
		x = -1;
		while (++x < size_x)
		{
			// if (x < 10 && y < 10)
			// {
				// printf("(%d * %d + %d)%d  == %d\n", y, x, x, y * x + x, i);
				if (y * size_x + x <= s)
				{
					if (y * size_x + x == i || (sdl->is_forked && y * size_x + x == j))
						SDL_SetRenderDrawColor(sdl->ren, 50, 155, 80, 255);
					else
						SDL_SetRenderDrawColor(sdl->ren, 10, 115, 40, 255);
				}

				else if (y * size_x + x == i || (sdl->is_forked && y * size_x + x == j))
					SDL_SetRenderDrawColor(sdl->ren, 10, 10, 10, 255);
				else
					SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
				SDL_RenderFillRect(sdl->ren, &(SDL_Rect){
					MAP_P_X + x * width + 1, MAP_P_Y + y * height + 1,
					width - 2, height - 2});
			// }
		}
	}
}
