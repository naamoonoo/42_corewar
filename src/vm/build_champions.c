/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:33:02 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/16 22:04:12 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

static int	champ_number_exists(t_arrlst *champions, int champ_number)
{
	int			i;
	t_champion	*champ;

	i = 0;
	while (i < champions->size)
	{
		champ = *(t_champion **)ft_arrlst_get(champions, i);
		if (champ->number == champ_number)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static int	add_with_number(t_arrlst *champions, int champ_number, char *file)
{
	t_champion *champ;

	champ = read_champion_from_file(file);
	if (champ == NULL)
		return (-1);
	champ->number = champ_number;
	if (champ_number_exists(champions, champ_number))
	{
		ft_fdprintf(2, "Error: Two champions cannot both be #%d!\n",
				champ_number);
		free_champions(champions);
		return (-1);
	}
	champ->color = rand();
	if (ft_arrlst_add(champions, &champ) == NULL)
	{
		ft_putstr_fd("Error: Failed to add champion.\n", 2);
		free_champions(champions);
		return (-1);
	}
	return (0);
}

static int	add_without_number(t_arrlst *champions, char *file)
{
	int		champ_number;

	champ_number = 1;
	while (champ_number_exists(champions, champ_number))
		champ_number++;
	return (add_with_number(champions, champ_number, file));
}

t_arrlst	*free_and_print_err(t_arrlst *champions)
{
	ft_putstr_fd("Error: Expected champion.\n", 2);
	free_champions(champions);
	return (NULL);
}

t_arrlst	*build_champions(int argc, char **argv, int *i)
{
	int			champ_number;
	t_arrlst	*champions;

	champions = ft_arrlst_new(sizeof(t_champion *));
	if (champions == NULL)
		return (NULL);
	while (*i < argc)
	{
		if (ft_strequ(argv[*i], "-n"))
		{
			champ_number = read_arg_number(argc, argv, i, NULL);
			if (*i >= argc)
				return (free_and_print_err(champions));
			if (add_with_number(champions, champ_number, argv[*i]) == -1)
				return (NULL);
		}
		else if (argv[*i][0] == '-')
			return (champions);
		else if (add_without_number(champions, argv[*i]) == -1)
			return (NULL);
		*i += 1;
	}
	return (champions);
}
