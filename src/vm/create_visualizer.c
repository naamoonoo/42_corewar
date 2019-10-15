/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_visualizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:52:08 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 17:43:30 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

static t_visualizer	*create_visualizer_from_flag(int argc, char **argv, int *i)
{
	if (argc == 2)
	{
		ft_error("Error: -v must be followed by an argument.\n", 0);
		return (NULL);
	}
	else if (ft_strequ(argv[2], "text"))
	{
		*i = 3;
		return (visualizer_text_new());
	}
	else if (ft_strequi(argv[2], "sdl"))
	{
		*i = 3;
		return (visualizer_sdl_new());
	}
	ft_error("Error: -v must be followed by either text or SDL.\n", 0);
	return (NULL);
}

t_visualizer		*create_visualizer(int argc, char **argv, int *i)
{
	if (argc == 1)
	{
		ft_printf("%s\n", "usage: ./corewar [-v text | SDL]"
				"[-dump nbr_cycles] [[-n number] champion1.cor] ...");
		return (NULL);
	}
	if (ft_strequ(argv[1], "-v"))
	{
		return (create_visualizer_from_flag(argc, argv, i));
	}
	else
	{
		*i = 1;
		return (visualizer_text_new());
	}
}
