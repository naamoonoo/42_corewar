/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 22:51:24 by hnam              #+#    #+#             */
/*   Updated: 2019/08/08 17:43:20 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_heat_map(t_filler *filler)
{
	int			y;
	int			x;
	static int	call = 0;

	if (call++ > 0)
		free_heat_map(filler);
	filler->heat_map = (int **)malloc(sizeof(int *) * (filler->map_size.y));
	y = -1;
	while (++y < filler->map_size.y)
	{
		filler->heat_map[y] = ft_memalloc(sizeof(int) * (filler->map_size.x));
		x = -1;
		while (++x < filler->map_size.x)
			filler->heat_map[y][x] = 999;
	}
	y = -1;
	while (++y < filler->map_size.y)
	{
		x = -1;
		while (++x < filler->map_size.x)
			if (ft_strchr(filler->p2, filler->map[y][x]))
				heat_map_maker(filler, x, y, 0);
	}
}

void	heat_map_maker(t_filler *filler, int x, int y, int from)
{
	int		**tab;
	t_cor	size;

	if (x < 0 || x > filler->map_size.x || y < 0 ||
		y > filler->map_size.y || ft_strchr(filler->p1, filler->map[y][x]))
		return ;
	tab = filler->heat_map;
	size = filler->map_size;
	if (from <= tab[y][x])
		tab[y][x] = from++;
	if (x - 1 >= 0 && (tab[y][x - 1] == 0 || tab[y][x - 1] > from)
		&& !ft_strchr(filler->p2, filler->map[y][x - 1]))
		heat_map_maker(filler, x - 1, y, from);
	if (x + 1 < size.x && (tab[y][x + 1] == 0 || tab[y][x + 1] > from)
		&& !ft_strchr(filler->p2, filler->map[y][x + 1]))
		heat_map_maker(filler, x + 1, y, from);
	if (y - 1 >= 0 && (tab[y - 1][x] == 0 || tab[y - 1][x] > from)
		&& !ft_strchr(filler->p2, filler->map[y - 1][x]))
		heat_map_maker(filler, x, y - 1, from);
	if (y + 1 < size.y && (tab[y + 1][x] == 0 || tab[y + 1][x] > from)
		&& !ft_strchr(filler->p2, filler->map[y + 1][x]))
		heat_map_maker(filler, x, y + 1, from);
}

void	free_heat_map(t_filler *f)
{
	int	y;

	y = -1;
	while (++y < f->map_size.y)
		free(f->heat_map[y]);
	free(f->heat_map);
}
