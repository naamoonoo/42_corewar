/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:47:30 by aderby            #+#    #+#             */
/*   Updated: 2019/08/06 20:35:39 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/asm.h"

static int	output_name_check(char *input_file, char *output_name) //TODO make this a static function for dasm
{
	char *ptr;

	ptr = ft_strchr(input_file, '.');
	if(ft_strnequ(input_file, output_name, ptr - input_file))
		return (1);
	return (0);
}

static int	disassemble(int *fd)//TODO move this to a disassemble file probably static to dasm
{
	char c;

	while (read(INPUT, &c, 1) > 0)
	{
			if (( int)c > 0 && (int)c <= 16)
			{
				write(OUTPUT, g_op_tab[(int)c - 1].name, ft_strlen(g_op_tab[(int)c - 1].name));
				if (g_op_tab[(int)c - 1].encode)
				{
					decode(fd, g_op_tab[(int)c - 1]);
					write(OUTPUT, "\n", 1);
				}
				else
				{
					no_decode(fd, g_op_tab[(int)c - 1]);
					write(OUTPUT, "\n", 1);
				}
			}
			else
				return (ft_error("The file could not be disassembled\n", 0));
	}
	return (1);
}

static int header_get(int *fd)
{
    header_t	header;
	int			bytes_read;

	bytes_read = read(INPUT, &header, sizeof(header_t));
	if (bytes_read == -1)
		return (ft_error("Read error.\n", 0));
	if (bytes_read < (int)sizeof(header_t))
		return (ft_error("Unexpected end of file.\n", 0));
    write(OUTPUT, ".name \"", 7);
	ft_putstr_fd(header.prog_name, OUTPUT);
    write(OUTPUT, "\"\n", 2);
    write(OUTPUT, ".comment \"", 10);
	ft_putstr_fd(header.comment, OUTPUT);
    write(OUTPUT, "\"\n\n", 3);
    return (1);
}

int			dasm(char *input_file, char *output_name, int *fd)
{
	if (!extension_check(input_file, ".cor"))
		return (ft_error("Invalid file type.\nLooking for <file>.cor\n", 0));
	if (!extension_check(output_name, ".s"))
		return (ft_error("Invalid file type.\nLooking for <file>.cor\n", 0));
	if (!output_name_check(input_file, output_name))
		return (ft_error("The 3rd parameter should match the <file>.cor file-name\n", 0));
	INPUT = open(input_file, O_RDONLY);
	OUTPUT = open(output_name, O_CREAT | O_RDWR, 0644);
	if (!INPUT)
		return (ft_error("The input file could not be opened\n", 0));
	if (!OUTPUT)
		return (ft_error("The output file could not be created\n", 0));
	if (!header_get(fd))
		return (0);
	if (!disassemble(fd))
		return (ft_error("Failed to disassemble the <file>.cor\n", 0));
	return (1);
}
