/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:49 by hnam              #+#    #+#             */
/*   Updated: 2019/08/19 22:38:14 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../lib/includes/ft_printf.h"
# include "../lib/includes/libft.h"

# include "SDL.h"
# include "SDL_ttf.h"

# define MAP_P_X 256
# define MAP_P_Y 176
# define MAP_SIZE_X 2048
# define MAP_SIZE_Y 1024

# define BTN_X sdl->e.button.x
# define BTN_Y sdl->e.button.y

# define KEY sdl->e.key.keysym.sym

# define R set.color.r
# define G set.color.g
# define B set.color.b
# define A set.color.a

# define C_BK (SDL_Color){0, 0, 0, 255}
# define C_WH (SDL_Color){255, 255, 255, 255}
# define C_BL (SDL_Color){0x36, 0x4f, 0x6b, 255}
# define C_GREY (SDL_Color){0xea, 0xea, 0xea, 255}
# define C_P1 (SDL_Color){0x11, 0x14, 0x4c, 255}
# define C_P2 (SDL_Color){0x3a, 0x96, 0x79, 255}
# define C_P3 (SDL_Color){0xfa, 0xbc, 0x60, 255}
# define C_P4 (SDL_Color){0xe1, 0x62, 0x62, 255}
# define C_BACK (SDL_Color){32, 101, 131, 255}

# define NUM_OF_INFO 14
# define NUM_OF_CHAMP 10

typedef struct		s_set
{
	char			*text;
	SDL_Rect		rect;
	SDL_Color		color;
}					t_set;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*scr;
	SDL_Renderer	*ren;
	SDL_Event		e;
	SDL_Texture		*tex[NUM_OF_INFO];
	SDL_Rect		rect[NUM_OF_INFO];
	SDL_Texture		*champ_tex[NUM_OF_CHAMP];
	SDL_Rect		champ_rect[NUM_OF_CHAMP];
	char			*curr_champs[NUM_OF_CHAMP];
	int				fd;
	char			*tmp;
	char			**champs;
	int				is_running;
	int				is_quit;
	int				nb_of_p;
	int				page;
	char			*selected_cmp[4];
	int				ready;
	int				w;
	int				h;
	TTF_Font		*font[2];
	int				is_forked;
}					t_sdl;

/*
**-----------------------main page---------------------------
*/

t_sdl				*sdl_init(void);

void				event_handler(t_sdl *sdl);
void				end_process(t_sdl *sdl);

/*
**-----------------------start page---------------------------
*/
void				render_start_page(t_sdl *sdl);
void				render_champs(t_sdl *sdl);
int					render_start_text(t_sdl *sdl);
int					render_start_box(t_sdl *sdl);
void				destroy_start_page(t_sdl *sdl);

int					is_clicked(t_sdl *sdl, SDL_Rect btn);
int					is_existed(t_sdl *sdl, char *clicked);
void				change_page(t_sdl *sdl);
void				select_player(t_sdl *sdl);
void				unselect_player(t_sdl *sdl);

void				render_text(t_sdl *sdl, int idx);
/*
**-----------------------play page---------------------------
*/
void				render_play_page(t_sdl *sdl);
void				render_play_box(t_sdl *sdl);
void				render_play_text(t_sdl *sdl);

void				render_empty_map(t_sdl *sdl, int size_x, int size_y);
void				render_map(t_sdl *sdl, int size_x, int size_y);


#endif
