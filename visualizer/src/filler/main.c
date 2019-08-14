/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 22:50:08 by hnam              #+#    #+#             */
/*   Updated: 2019/08/08 18:08:14 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	main(void)
{
	t_filler	*filler;
	char		*line;

	line = NULL;
	filler = ft_memalloc(sizeof(t_filler));
	if (!filler->p1)
		get_player_info(filler);
	while (1)
	{
		get_data(filler);
		put_piece(filler);
	}
	free_char_pp(filler->map);
	free_char_pp(filler->piece);
	free_heat_map(filler);
	return (0);
}
