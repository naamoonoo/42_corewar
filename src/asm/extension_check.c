/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:47:30 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:03:46 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int	extension_check(const char *file, char *extension)
{
	char *ptr;

	if ((ptr = ft_strchr(file, '.')))
		if (ft_strequ(ptr, extension))
			return (1);
	return (0);
}
