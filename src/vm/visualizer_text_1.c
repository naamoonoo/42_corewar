/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_text_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:02:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/13 21:10:07 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

void	visualizer_text_init(void *data)
{
	ft_printf("init\n");
	UNUSED(data);
}

void	visualizer_text_instruction_read(void *data, t_mem *address)
{
	ft_printf("instruction %d read at address %p\n", address->data, address);
	UNUSED(data);
}

void	visualizer_text_instruction_fired(void *data, t_mem *address)
{
	ft_printf("instruction fired at address %p\n", address);
	UNUSED(data);
}
