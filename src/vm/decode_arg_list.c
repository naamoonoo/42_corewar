/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_arg_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:12:13 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/16 21:54:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"
#include "../../include/op.h"

/*
** void * args store different values depending on the arg type:
**    REG   Stores a pointer to the value in one of the program's registers
**    IND   Stores a t_mem * pointer to a memory location
**    DIR   Does not store a pointer. Stores the raw int data cast to a void *
*/

static void	*parse_arg_dir(t_mem **mem, int dir_ind)
{
	long value;

	if (dir_ind)
	{
		value = mem_read_ind(*mem);
		*mem = mem_ptr_add(*mem, 2);
		return (void *)value;
	}
	else
	{
		value = mem_read_dir_silent(*mem);
		*mem = mem_ptr_add(*mem, 4);
		return (void *)value;
	}
}

static void	*parse_arg_ind(t_mem **mem, t_process *caller, int using_idx_mod)
{
	int offset;

	offset = mem_read_ind(*mem);
	*mem = mem_ptr_add(*mem, 2);
	if (using_idx_mod)
		offset = offset % IDX_MOD;
	else
		offset = offset % MEM_SIZE;
	return (mem_ptr_add(caller->pc, offset));
}

static void	*parse_arg_reg(t_mem **mem, t_process *caller)
{
	int reg;

	reg = (*mem)->data;
	*mem = (*mem)->next;
	if (reg < 1 || reg > REG_NUMBER)
		return (NULL);
	return (caller->registers + reg);
}

static int	decode_stub(t_arg_list *args, t_op op, t_process *caller, int uim)
{
	t_mem	*mem;
	char	acb;
	int		i;
	int		valid;

	acb = caller->pc->next->data;
	mem = caller->pc->next->next;
	valid = TRUE;
	i = 0;
	while (i < op.param_num)
	{
		args->arg_types[i] = (acb >> (6 - 2 * i)) & 3;
		if (args->arg_types[i] == DIR_CODE)
			args->args[i] = parse_arg_dir(&mem, op.dir_ind);
		else if (args->arg_types[i] == IND_CODE)
			args->args[i] = parse_arg_ind(&mem, caller, uim);
		else if (args->arg_types[i] == REG_CODE)
			args->args[i] = parse_arg_reg(&mem, caller);
		else
			valid = FALSE;
		i++;
	}
	caller->pc = mem;
	return (valid);
}

t_arg_list	*decode_arg_list(t_op op, t_process *caller, int uses_idx_mod)
{
	t_arg_list *args;

	args = (t_arg_list *)malloc(sizeof(t_arg_list));
	if (args == NULL)
		return (NULL);
	if (!decode_stub(args, op, caller, uses_idx_mod))
	{
		free(args);
		return (NULL);
	}
	if (valid_arg_list(op, args))
		return (args);
	else
	{
		free(args);
		return (NULL);
	}
}
