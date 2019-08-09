/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:47:30 by aderby            #+#    #+#             */
/*   Updated: 2019/08/06 20:36:28 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/asm.h"

int	get_name(char *file)
{
	char 	*name;
	char 	*ptr;
	int		fd;

	ptr = ft_strchr(file, '.');
	ptr = ft_strsub(file, 0, file - ptr);
	name = ft_strjoin(file, ".cor");
	free(ptr);
	fd = open(name, O_CREAT | O_RDWR, 0644);
	free(name);
	if (!fd)
		return (ft_error("The output file could not be created.\n", 0));
	return (fd);
}

int	assemble(char *file)
{
	int fd[2];

	if (!extension_check(file, ".s"))
		return (ft_error("The file must have the .cor extension\n", 0));
	INPUT = open(file, O_RDONLY);
	if (!(OUTPUT = get_name(file)))
		return (ft_error("Unable to create the output file.\n", 0));
	if (fd <= 0)
		return (ft_error("Unable to open <file>.s\n", 0));

	return (1);
}
//TODO You need to free the file names if they were allocated for dasm and asm
int	main(int ac, char **av)
{
	if (ac == 4)
	{
		if (!ft_strequ(av[1], "-d"))
			return (ft_error("./asm | [-d file.cor] | file.s\n", 1));
		if (!dasm(av[2], av[3], (int[2]){0,0}))
			return (ft_error("The <file>.cor could not be disassembled\n", 1));
		return (0);//complete this using nicks printf
	}
	else if (ac == 2)
	{
		assemble(av[1]);
		ft_putstr("There are a correct number of args here too\n");//TODO replace this with an assembler
	}
	else
		return (ft_error("./asm | [-d file.cor] | file.s\n", 1));
}
