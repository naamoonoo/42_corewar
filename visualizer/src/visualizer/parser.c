/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:04:15 by hnam              #+#    #+#             */
/*   Updated: 2019/08/07 22:48:15 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	parse_data(t_f *f, t_sdl *sdl)
{
	while (sdl->is_running && get_next_line(f->fd, &(f->line)) >= 0)
	{
		if (ft_strstr(f->line, "fin") || ft_strstr(f->line, "error")
			|| f->line == NULL)
			sdl->is_running = 0;
		if (ft_strstr(f->line, "got") && f->round++)
		{
			free(f->line);
			break ;
		}
		if (!f->round && ft_strstr(f->line, "$$$ exec"))
			player_info(f, f->line);
		else if (!f->round && ft_strstr(f->line, "Plateau"))
			info_of(&(f->map_size), f->line);
		if (ft_strstr(f->line, "Plateau"))
			current_map(f, f->map_size.y + 1, f->fd);
		else if (ft_strstr(f->line, "Piece"))
		{
			info_of(&(f->piece_size), f->line);
			current_piece(f, f->piece_size.y, f->fd);
			free(f->line);
			break ;
		}
		free(f->line);
	}
}

void	current_piece(t_f *f, int lines, int fd)
{
	char		*tmp;
	int			line;
	static int	call = 0;

	line = -1;
	tmp = NULL;
	if (call++ > 0)
		free_char_pp(f->p);
	f->p = (char **)malloc(sizeof(char *) * (lines + 1));
	f->p[lines] = NULL;
	while (++line < lines && get_next_line(fd, &tmp) > 0)
	{
		f->p[line] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

void	player_info(t_f *f, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(line, '/');
	while (arr[i] && arr[i + 1])
		i++;
	if (ft_strstr(line, "p1"))
	{
		f->p1_name = ft_strsub(arr[i], 0, ft_strchr_idx(arr[i], '.'));
		f->p1 = "oO";
		f->c_p1 = (SDL_Color){0xf7, 0Xb7, 0X31, 255};
	}
	else if (ft_strstr(line, "p2"))
	{
		f->p2_name = ft_strsub(arr[i], 0, ft_strchr_idx(arr[i], '.'));
		f->p2 = "xX";
		f->c_p2 = (SDL_Color){0x38, 0x67, 0xd6, 255};
	}
	free_char_pp(arr);
}

void	info_of(t_cor *size, char *line)
{
	char	**arr;
	char	*tmp;

	if (ft_c_cnt(line, ' ') != 2)
		return ;
	tmp = ft_strtrim_by(line, ':');
	arr = ft_strsplit(tmp, ' ');
	free(tmp);
	size->y = ft_atoi(arr[1]);
	size->x = ft_atoi(arr[2]);
	free_char_pp(arr);
}

void	current_map(t_f *f, int lines, int fd)
{
	char		*tmp;
	int			line;
	static int	call = 0;

	line = -1;
	tmp = NULL;
	if (call++ > 0)
		free_char_pp(f->m);
	f->m = (char **)malloc(sizeof(char *) * lines);
	f->m[lines - 1] = NULL;
	while (++line < lines && get_next_line(fd, &tmp) > 0)
	{
		if (line != 0)
			f->m[line - 1] = ft_strdup(tmp + 4);
		free(tmp);
	}
	get_score(f);
}
