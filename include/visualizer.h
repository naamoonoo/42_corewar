/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:49 by hnam              #+#    #+#             */
/*   Updated: 2019/09/27 15:10:58 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../libft/libft.h"
# include "corewar.h"

# include <SDL.h>
# include <SDL_ttf.h>

# define WIDTH 2560
# define HEIGHT 1600
# define MAP_P_X 130
# define MAP_P_Y 60
# define MAP_SIZE_X 2360
# define MAP_SIZE_Y 1400
# define BOX_W (MAP_SIZE_X / 64)
# define BOX_H (MAP_SIZE_Y / 64)
# define CHUNK 10000

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
# define C_P1 (SDL_Color){0x41, 0x69, 0xe1, 255}
# define C_P2 (SDL_Color){0x3a, 0x96, 0x79, 255}
# define C_P3 (SDL_Color){0xe1, 0x62, 0x62, 255}
# define C_P4 (SDL_Color){0xfa, 0xbc, 0x60, 255}
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
	t_set			selected_cmp[MAX_PLAYERS];
	int				score[MAX_PLAYERS];
	char			*curr_champs[NUM_OF_CHAMP];
	int				nb_of_p;
	int				winner;
	char			**champs;
	int				is_running;
	int				is_quit;
	int				in_show;
	int				is_init;
	int				page;
	int				ready;
	t_mem			*mem_start;
	TTF_Font		*font[2];
}					t_sdl;

t_sdl	*sdl_init(void);

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
SDL_Color			get_color_of(char *champ, t_sdl *sdl);
void				color_adjust(SDL_Color *color, double percent);

void				render_map(t_sdl *sdl);
void				render_status_bar(t_sdl *sdl);
void				render_only_name(t_sdl *sdl, char *text, SDL_Rect *rect);
void				render_finish(t_sdl *sdl);
void				render_cycle_box(t_sdl *sdl, int cycle);

void				free_char_pp(char **arr);
int					get_small(int a, int b);
char				*base_itoa(uint64_t n, int str_base, int len);
/*
**-----------------------visualizer---------------------------
*/
void				visualizer_sdl_init(void *data, int argc, char **argv);
void				visualizer_sdl_instruction_read(void *data, t_mem *address);
void				visualizer_sdl_instruction_fired(void *data,
															t_mem *address);
void				visualizer_sdl_process_lived(void *data, t_process *process,
												int champ, char *champ_name);
void				visualizer_sdl_memory_read(void *data, t_mem *address,
												int value, t_process *process);
void				visualizer_sdl_memory_written(void *data, t_mem *address,
												int value, t_process *process);
void				visualizer_sdl_render(void *data, t_vm *vm);
int					visualizer_sdl_program_active(void *data);
void				visualizer_sdl_game_over(void *data, t_vm *vm);
void				visualizer_sdl_cleanup(void *data);
t_arrlst			*visualizer_sdl_select_champs(void *data);
void				visualizer_sdl_use_champs(void *data, t_arrlst *champs);
void				visualizer_sdl_sleep(void *data);
#endif
