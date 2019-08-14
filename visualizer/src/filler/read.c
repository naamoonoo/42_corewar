/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 22:53:49 by hnam              #+#    #+#             */
/*   Updated: 2019/08/08 18:08:43 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_data(t_filler *filler)
{
	char	*line;

	line = NULL;
	while (gnl_linked_lst(STDIN_FILENO, &line) > 0)
	{
		if (ft_strstr(line, "Plateau"))
		{
			get_info_of(&(filler->map_size), line);
			get_current_map(filler, filler->map_size.y + 1);
		}
		else if (ft_strstr(line, "Piece"))
		{
			get_info_of(&(filler->piece_size), line);
			free(line);
			get_current_piece(filler, filler->piece_size.y);
			break ;
		}
		free(line);
	}
}

void	get_player_info(t_filler *filler)
{
	static int	nb_of_p = 0;
	char		**arr;
	char		*line;

	line = NULL;
	arr = NULL;
	if (nb_of_p++)
		return ;
	while (gnl_linked_lst(0, &line) > 0)
	{
		if (ft_strstr(line, "$$$ exec"))
			arr = ft_strsplit(line, ' ');
		free(line);
		if (arr)
			break ;
	}
	if (strcmp(arr[0], "$$$") || strcmp(arr[1], "exec") || strcmp(arr[3], ":"))
		return ;
	filler->p1 = !strcmp(arr[2], "p1") ? "oO" : "xX";
	filler->p2 = !strcmp(arr[2], "p1") ? "xX" : "oO";
	free_char_pp(arr);
}

void	get_info_of(t_cor *size, char *line)
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

void	get_current_map(t_filler *filler, int lines)
{
	char		*tmp;
	int			line;
	static int	call = 0;

	line = -1;
	tmp = NULL;
	if (call++ > 0)
		free_char_pp(filler->map);
	filler->map = (char **)malloc(sizeof(char *) * lines);
	filler->map[lines - 1] = NULL;
	while (++line < lines && gnl_linked_lst(STDIN_FILENO, &tmp) > 0)
	{
		if (line != 0)
			filler->map[line - 1] = ft_strdup(tmp + 4);
		free(tmp);
	}
}

void	get_current_piece(t_filler *filler, int lines)
{
	char		*tmp;
	int			line;
	static int	call = 0;

	line = -1;
	tmp = NULL;
	if (call++ > 0)
		free_char_pp(filler->piece);
	filler->piece = (char **)malloc(sizeof(char *) * (lines + 1));
	filler->piece[lines] = NULL;
	while (++line < lines && gnl_linked_lst(STDIN_FILENO, &tmp) > 0)
	{
		filler->piece[line] = ft_strdup(tmp);
		free(tmp);
		if (line == lines - 1)
			break ;
	}
}
