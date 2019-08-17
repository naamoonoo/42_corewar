/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:49 by hnam              #+#    #+#             */
/*   Updated: 2019/08/16 22:03:48 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "filler.h"
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
# define C_ORG (SDL_Color){200, 100, 20, 255}
# define MAP_Y f->map_size.y
# define MAP_X f->map_size.x
# define PIECE_Y f->piece_size.y
# define PIECE_X f->piece_size.x
# define PIECE_P_X 850
# define PIECE_P_Y 140
# define NUM_OF_INFO 20

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
	int				is_running;
	int				is_quit;
	int				nb_of_p;
	t_set			selected_cmp[4];
	int				ready_to_start;
	int				w;
	int				h;
	TTF_Font		*font[2];
	int				is_forked;
}					t_sdl;
typedef struct		s_f
{
	int				fd;
	int				round;
	char			*line;
	char			*p1_name;
	char			*p1;
	SDL_Color		c_p1;
	int				s_p1;
	char			*p2_name;
	char			*p2;
	SDL_Color		c_p2;
	int				s_p2;
	t_cor			map_size;
	char			**m;
	int				auto_fill;
	t_cor			piece_size;
	char			**p;
}					t_f;

typedef struct		s_button
{
	SDL_Rect		start;
	SDL_Color		c_start;
}					t_btn;

t_sdl				*sdl_init(void);

void				render_empty_map(t_sdl *sdl, int size_x, int size_y);
void				render_map(t_sdl *sdl, int size_x, int size_y);

void				event_handler(t_sdl *sdl, t_btn *btn);
void				end_process(t_sdl *sdl);

t_btn	*btn_init(void);
int	is_clicked(t_sdl *sdl, SDL_Rect btn);
int	render_start_text(t_sdl *sdl);
int	render_start_btn(t_sdl *sdl, t_btn *btn);
int	render_start_box(t_sdl *sdl);
void	select_player(t_sdl *sdl);

void	render_text(t_sdl *sdl, int idx);


void				parse_data(t_f *f, t_sdl *sdl);
void				player_info(t_f *f, char *line);
void				current_piece(t_f *f, int lines, int fd);
void				current_map(t_f *f, int lines, int fd);
void				info_of(t_cor *size, char *line);

void				render_piece(t_sdl *sdl, t_f *f);
void				fuck_norm(t_sdl *sdl, t_f *f, int y, int x);
void				render_status_bar(t_sdl *sdl, t_f *f);

void				render_text2(t_sdl *sdl);
void				render_pallete(t_sdl *sdl);
void				get_text_and_rect(char *text, t_sdl *sdl,
						int idx, SDL_Color color);

void				get_color_by(char p, t_f *f, t_sdl *sdl);
void				get_score(t_f *f);

#endif
