/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:47:30 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 13:13:43 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int	output_name_check(char *input_file, char *output_name)
{
	char *ptr;

	ptr = ft_strchr(input_file, '.');
	if (ft_strnequ(input_file, output_name, ptr - input_file))
		return (1);
	return (0);
}

int	disassemble(int *fd, char c)
{
	while (read(INPUT, &c, 1) > 0)
	{
		if ((int)c > 0 && (int)c <= 16)
		{
			write(OUTPUT, g_op_tab[(int)c - 1].name,
					ft_strlen(g_op_tab[(int)c - 1].name));
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

int	comment_name_get(int *fd)
{
	t_header	tmp;

	read(INPUT, (char[4]){0}, 4);
	read(INPUT, tmp.prog_name, PROG_NAME_LENGTH + 1);
	read(INPUT, (char[8]){0}, 8);
	read(INPUT, tmp.comment, COMMENT_LENGTH + 1);
	write(OUTPUT, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	write(OUTPUT, " \"", 2);
	write(OUTPUT, tmp.prog_name, ft_strlen(tmp.prog_name));
	write(OUTPUT, "\"\n", 2);
	write(OUTPUT, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING));
	write(OUTPUT, " \"", 2);
	write(OUTPUT, tmp.comment, ft_strlen(tmp.comment));
	write(OUTPUT, "\"\n\n", 3);
	read(INPUT, (char[4]){0}, 4);
	return (1);
}

int	dasm(char *input_file, char *output_name, int *fd)
{
	if (!extension_check(input_file, ".cor"))
		return (ft_error("Invalid file type.\nLooking for <file>.cor\n", 0));
	if (!extension_check(output_name, ".s"))
		return (ft_error("Invalid file type.\nLooking for <file>.cor\n", 0));
	if (!output_name_check(input_file, output_name))
		return (ft_error("The 3rd parameter should match <file>.cor\n", 0));
	INPUT = open(input_file, O_RDONLY);
	OUTPUT = open(output_name, O_CREAT | O_RDWR, 0644);
	if (!INPUT)
		return (ft_error("The input file could not be opened\n", 0));
	if (!OUTPUT)
		return (ft_error("The output file could not be created\n", 0));
	comment_name_get(fd);
	if (!disassemble(fd, '\0'))
		return (ft_error("Failed to disassemble the <file>.cor\n", 0));
	return (1);
}
