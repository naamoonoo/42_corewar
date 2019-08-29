/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:54:36 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:06:00 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	write_int(int value, int *fd)
{
	write(OUTPUT, (char[1]){(value >> 24)}, 1);
	write(OUTPUT, (char[1]){(value >> 16)}, 1);
	write(OUTPUT, (char[1]){(value >> 8)}, 1);
	write(OUTPUT, (char[1]){value}, 1);
}

void	write_short(short value, int *fd)
{
	write(OUTPUT, (char[1]){(value >> 8)}, 1);
	write(OUTPUT, (char[1]){value}, 1);
}
