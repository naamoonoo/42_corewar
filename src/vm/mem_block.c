/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:43:12 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/07 18:48:32 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

t_mem	*mem_block_create(unsigned int size)
{
	t_mem			*mem_block;
	unsigned int	i;

	if (size == 0)
		return (NULL);
	mem_block = (t_mem *)malloc(size * sizeof(t_mem));
	if (mem_block == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		mem_block[i].data = 0;
		mem_block[i].prev = mem_block + i - 1;
		mem_block[i].next = mem_block + i + 1;
		i++;
	}
	mem_block[0].prev = mem_block + size - 1;
	mem_block[size - 1].next = mem_block;
	return (mem_block);
}

void	mem_block_free(t_mem *mem_block)
{
	free(mem_block);
}
