/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:11:18 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/08 18:16:50 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

#define BADREG(R) R < 0 || R > REG_NUMBER
#define UNUSED(X) (void)X

void		in_add(t_vm *vm, t_process *process)
{
	t_mem	*ptr;
	int		reg1;
	int		reg2;
	int		reg3;
	int		sum;

	UNUSED(vm);
	ptr = process->pc->next;
	reg1 = ptr->data;
	ptr = ptr->next;
	reg2 = ptr->data;
	reg3 = ptr->next->data;
	;
	if (BADREG(reg1) || BADREG(reg2) || BADREG(reg3))
		return ;
	sum = process->registers[reg1] + process->registers[reg2];
	process->registers[reg3] = sum;
	process->carry = (sum == 0);
}
