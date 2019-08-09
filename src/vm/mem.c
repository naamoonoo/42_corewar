/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:15:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/08 14:53:03 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

short	mem_read_ind(t_mem *ptr)
{
	char	output[2];

	*output = ptr->next->data;
	*(output + 1) = ptr->data;
	return *((short *)output);
}

int		mem_read_dir(t_mem *ptr)
{
	char	output[4];
	int		i;

	i = 0;
	while (i < 4)
	{
		*(output + 3 - i) = ptr->data;
		ptr = ptr->next;
		i++;
	}
	return *((int *)output);
}

void	mem_write_ind(t_mem *ptr, short value)
{
	char	*input;

	input = (void *)&value;
	ptr->data = input[1];
	ptr->next->data = input[0];
}

void	mem_write_dir(t_mem *ptr, int value)
{
	char	*input;
	int		i;

	input = (void *)&value;
	i = 0;
	while (i < 4)
	{
		ptr->data = input[3 - i];
		ptr = ptr->next;
		i++;
	}
}

t_mem	*mem_ptr_add(t_mem *ptr, int offset)
{
	while (offset > 0)
	{
		ptr = ptr->next;
		offset--;
	}
	while (offset < 0)
	{
		ptr = ptr->prev;
		offset++;
	}
	return (ptr);
}
