/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:47:30 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 17:07:41 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int	main(int ac, char **av)
{
	if (ac == 4)
	{
		if (!ft_strequ(av[1], "-d"))
			return (ft_error("./asm | [-d file.cor] | file.s\n", 1));
		if (!dasm(av[2], av[3], (int[2]){0, 0}))
			return (ft_error("The <file>.cor could not be disassembled\n", 1));
		return (0);
	}
	else if (ac == 2)
		assemble(av[1]);
	else
		return (ft_error("./asm | [-d file.cor] | file.s\n", 1));
}
