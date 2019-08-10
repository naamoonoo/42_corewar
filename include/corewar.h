/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:12:16 by aderby            #+#    #+#             */
/*   Updated: 2019/08/09 01:10:52 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# define FALSE 0
# define TRUE 1
# define AARON 1
# define AWESOME 1
# define BADREG(R) R < 0 || R > REG_NUMBER
# define UNUSED(X) (void)X


# include <stdlib.h>
# include <stdio.h>

# include "../include/op.h"
# include "../libft/libft.h"

typedef struct			s_mem
{
	char				data;
	struct s_mem		*prev;
	struct s_mem		*next;
}						t_mem;

typedef struct s_process	t_process;

typedef struct			s_vm
{
	struct s_process	*p_list;
	struct s_process	*last_alive;
	int					cycles_to_die;
	int					delta;
}						t_vm;

typedef	void			(*t_instruction)(t_vm *vm, t_process *process);

struct					s_process
{
	int					pid;
	int					registers[REG_NUMBER + 1];
	int					carry;
	t_mem				*pc;
	t_instruction		instruction;
	int					alive;
	t_process			*next;
	int					cycles_to_wait;
};

short					mem_read_ind(t_mem *ptr);
int						mem_read_dir(t_mem *ptr);
void					mem_write_ind(t_mem *ptr, short value);
void					mem_write_dir(t_mem *ptr, int value);
t_mem					*mem_ptr_add(t_mem *ptr, int offset);

t_mem					*mem_block_create(unsigned int size);
void					mem_block_free(t_mem *mem_block);

t_process				*process_new(int pid, t_mem *pc);

void					in_live(t_vm *vm, t_process *process);
void					in_ld(t_vm *vm, t_process *process);
void					in_st(t_vm *vm, t_process *process);
void					in_add(t_vm *vm, t_process *process);
void					in_sub(t_vm *vm, t_process *process);
void					in_and(t_vm *vm, t_process *process);
void					in_or(t_vm *vm, t_process *process);
void					in_xor(t_vm *vm, t_process *process);
void					in_zjmp(t_vm *vm, t_process *process);
void					in_ldi(t_vm *vm, t_process *process);
//void					in_sti(t_vm *vm, t_process *process);
void					in_fork(t_vm *vm, t_process *process);
void					in_lld(t_vm *vm, t_process *process);
void					in_lldi(t_vm *vm, t_process *process);
void					in_lfork(t_vm *vm, t_process *process);
//void					in_aff(t_vm *vm, t_process *process);

void					push_to_stack(t_process **stack, t_process *process);
void					purge_list(t_process **p_list);
void					decriment_cycles(t_vm *vm, t_process **process, int cycle_decriment);
int						get_min_cycles_to_wait(t_process *p_list, int cycle_to_die);
t_process				*scheduler(t_vm *vm);

#endif
