/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 22:54:37 by hnam              #+#    #+#             */
/*   Updated: 2019/08/07 22:54:37 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_piece(t_filler *filler)
{
	get_heat_map(filler);
	filler->heat_score = 999;
	filler->best_pos = (t_cor){-1, -1};
	get_best_position(filler);
	if (filler->best_pos.x < 0 && filler->best_pos.y < 0)
		filler->best_pos = (t_cor){0, 0};
	FP("%d %d\n", filler->best_pos.y, filler->best_pos.x);
}

void	get_best_position(t_filler *filler)
{
	int		ix;
	int		iy;
	int		score;

	iy = -1;
	while (++iy < filler->map_size.y)
	{
		ix = -1;
		while (++ix < filler->map_size.x)
		{
			if (ix < filler->map_size.x &&
				iy < filler->map_size.y &&
				!ft_strchr(filler->p2, filler->map[iy][ix]) &&
				is_valid(filler, ix, iy) &&
				(score = get_heat_score(filler, ix, iy)) <= filler->heat_score)
			{
				filler->best_pos = (t_cor){ix, iy};
				filler->heat_score = score;
			}
		}
	}
}

int		is_valid(t_filler *filler, int x, int y)
{
	t_cor	t;
	int		valid_pos;

	t.y = -1;
	valid_pos = 0;
	if (x + filler->piece_size.x >= filler->map_size.x + 1 ||
		y + filler->piece_size.y >= filler->map_size.y + 1)
		return (0);
	while (++t.y < filler->piece_size.y)
	{
		t.x = -1;
		while (++t.x < filler->piece_size.x)
		{
			if (t.y + y < filler->map_size.y && t.x + x < filler->map_size.x
				&& filler->piece[t.y][t.x] == '*')
			{
				if (ft_strchr(filler->p1, filler->map[t.y + y][t.x + x]))
					valid_pos += 1;
				if (ft_strchr(filler->p2, filler->map[t.y + y][t.x + x]))
					return (0);
			}
		}
	}
	return (valid_pos == 1);
}

int		get_heat_score(t_filler *filler, int x, int y)
{
	t_cor	t;
	int		min;

	t.y = -1;
	min = 999;
	while (++t.y < filler->piece_size.y)
	{
		t.x = -1;
		while (++t.x < filler->piece_size.x)
			if (filler->heat_map[t.y + y][t.x + x] <= min)
				min = filler->heat_map[t.y + y][t.x + x];
	}
	return (min);
}
