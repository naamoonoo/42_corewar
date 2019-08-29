/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction_params.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 09:18:49 by aderby            #+#    #+#             */
/*   Updated: 2019/08/21 10:11:27 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

char	*read_dir_ind(int *fd)
{
	unsigned short	output;
	short			reverse;
	char			*number;

	read(INPUT, &output, 2);
	reverse = (0xFF00 & (output << 8)) + (0x00FF & (output >> 8));
	number = ft_itoa(reverse);
	return (number);
}

char	*read_dir(int *fd)
{
	unsigned int	output;
	unsigned int	reverse;
	char			*number;

	read(INPUT, &output, 4);
	reverse = 0x000000FF & output;
	reverse = (reverse << 8) + ((0x0000FF00 & output) >> 8);
	reverse = (reverse << 8) + ((0x00FF0000 & output) >> 16);
	reverse = (reverse << 8) + ((0xFF000000 & output) >> 24);
	number = ft_itoa(reverse);
	return (number);
}

void	parse_direct(int *fd, t_op op_tab)
{
	char	*number;
	char	direct;

	direct = DIRECT_CHAR;
	if (op_tab.dir_ind)
		number = read_dir_ind(fd);
	else
		number = read_dir(fd);
	write(OUTPUT, " ", 1);
	write(OUTPUT, &direct, 1);
	write(OUTPUT, number, ft_strlen(number));
	free(number);
}

void	parse_indirect(int *fd)
{
	unsigned short	output;
	short			reverse;
	char			*number;

	read(INPUT, &output, 2);
	reverse = (0xFF00 & (output << 8)) + (0x00FF & (output >> 8));
	write(OUTPUT, " ", 1);
	number = ft_itoa(reverse);
	write(OUTPUT, number, ft_strlen(number));
	free(number);
}

void	parse_registry(int *fd)
{
	char	c;
	char	*number;

	read(INPUT, &c, 1);
	number = ft_itoa((int)c);
	write(OUTPUT, " r", 2);
	write(OUTPUT, number, ft_strlen(number));
	free(number);
}
