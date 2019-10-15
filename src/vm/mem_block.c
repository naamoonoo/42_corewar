/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:43:12 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/27 19:04:30 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	mem_dump(t_mem *mem)
{
	t_mem	*ptr;
	int		len;

	ptr = mem;
	len = 0;
	ft_printf("\n[ ");
	while (TRUE)
	{
		len++;
		if (ptr->next == mem)
		{
			ft_printf("%.2hhX ]\n", ptr->data);
			break ;
		}
		else if (len == 32)
		{
			ft_printf("%.2hhX ]\n[ ", ptr->data);
			len = 0;
		}
		else
			ft_printf("%.2hhX ", ptr->data);
		ptr = ptr->next;
	}
}

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
		mem_block[i].owner = NULL;
		mem_block[i].text = NULL;
		mem_block[i].is_instruction = FALSE;
		mem_block[i].is_pc = FALSE;
		mem_block[i].tex = NULL;
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

void	mem_write_from_buffer(t_mem *mem, char *buff, unsigned int size,
		t_champion *champ)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		mem->data = buff[i];
		mem->owner = champ->filename;
		mem = mem->next;
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
