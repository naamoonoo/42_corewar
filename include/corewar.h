/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:12:16 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 19:06:56 by nwhitlow         ###   ########.fr       */
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
# define MAX_OPS 16

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "../include/op.h"
# include "../libft/libft.h"
# include <SDL.h>
# include <SDL_ttf.h>

typedef struct			s_mem
{
	char				data;
	struct s_mem		*prev;
	struct s_mem		*next;
	char				*owner;
	int					is_instruction;
	int					is_pc;
	char				*text;
	SDL_Texture			*tex;
	SDL_Rect			rect;
}						t_mem;

typedef struct s_process	t_process;

typedef struct			s_champion
{
	int					number;
	char				*name;
	char				*filename;
	unsigned int		size;
	char				*comment;
	char				bytecode[CHAMP_MAX_SIZE];
	int					color;
}						t_champion;

typedef struct s_visualizer	t_visualizer;

typedef struct			s_vm
{
	int					num_champions;
	t_champion			*champions[MAX_PLAYERS];
	t_mem				*memory;
	struct s_process	*p_list;
	int					last_alive;
	int					lives_this_round;
	int					rounds_since_decrease;
	int					cycles_to_die;
	int					delta;
	int					total_cycles;
	t_visualizer		*gv;
	int					total_processes;
	int					next_available_pid;
	int					dump;
	int					dump_after;
}						t_vm;

typedef	void			(*t_instruction)
						(t_vm *vm, t_process *process, t_visualizer *gv);

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
	t_champion			*owner;
	int					needs_to_be_prepared_on_the_next_cycle;
};

struct					s_visualizer
{
	void				*data;
	t_mem				*mem_start;
	void				(*init)(void *gv_data, int argc, char **argv);
	void				(*instruction_read)(void *gv_data, t_mem *address);
	void				(*instruction_fired)(void *gv_data, t_mem *address);
	void				(*process_lived)(void *gv_data, t_process *process,
			int champ, char *champ_name);
	void				(*memory_read)(void *gv_data, t_mem *address, int value,
										t_process *process);
	void				(*memory_written)(void *gv_data, t_mem *address,
										int value, t_process *process);
	void				(*render)(void *gv_data, t_vm *vm);
	int					(*program_active)(void *gv_data);
	void				(*game_over)(void *gv_data, t_vm *vm);
	void				(*cleanup)(void *gv_data);
	t_arrlst			*(*select_champs)(void *data);
	void				(*use_champs)(void *gv_data, t_arrlst *champs);
	void				(*sleep)(void *gv_data);
	void				(*silence)(t_visualizer *gv);
	t_process			*process;
};

typedef struct			s_arg_list
{
	t_arg_type			arg_types[4];
	void				*args[4];
}						t_arg_list;

typedef struct			s_things
{
	int					argc;
	char				**argv;
	int					i;
	t_visualizer		*gv;
	int					dump;
	int					dump_after;
	t_arrlst			*champions;
	t_vm				*vm;
}						t_things;

short					mem_read_ind(t_mem *ptr);
int						mem_read_dir_silent(t_mem *ptr);
int						mem_read_dir(t_mem *pt, t_visualizer *gv, t_process *p);
void					mem_write_ind(t_mem *ptr, short value);
void					mem_write_dir(t_mem *ptr, int value,
										t_visualizer *gv, t_process *p);
t_mem					*mem_ptr_add(t_mem *ptr, int offset);

t_mem					*mem_block_create(unsigned int size);
void					mem_block_free(t_mem *mem_block);
void					mem_dump(t_mem *mem);
void					mem_write_from_buffer(t_mem *mem,
							char *buff, unsigned int size, t_champion *champ);

t_process				*process_new(int pid, t_mem *pc);
void					process_prepare_instruction(t_process *process,
													t_visualizer *gv);

t_champion				*read_champion_from_file(char *file);
void					free_champion(t_champion *champ);
void					free_champions(t_arrlst *champions);

char					*vm_get_champ_name(t_vm *vm, int champ_id);
t_vm					*vm_new(t_arrlst *champions, t_visualizer *gv);
void					vm_free(t_vm *vm);

int						valid_arg_list(t_op op, t_arg_list *args);
t_arg_list				*decode_arg_list(t_op op, t_process *caller,
								int uses_idx_mod);
int						arg_list_read(t_arg_list *args, int n,
										t_visualizer *gv, t_process *p);
void					arg_list_write(t_arg_list *args, int n,
										int value, t_visualizer *gv);
void					arg_list_print(t_arg_list *args);

void					in_live(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_ld(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_st(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_add(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_sub(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_and(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_or(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_xor(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_zjmp(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_ldi(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_sti(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_fork(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_lld(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_lldi(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_lfork(t_vm *vm, t_process *proc, t_visualizer *gv);
void					in_aff(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_lt(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_gt(t_vm *vm, t_process *process, t_visualizer *gv);
void					in_aa(t_vm *vm, t_process *process, t_visualizer *gv);

void					push_to_stack(t_process **stack, t_process *process);
void					purge_list(t_process **p_list);
void					decriment_cycles(t_vm *vm, t_process **process,
								int cycle_decriment);
int						get_min_cycles_to_wait(t_process *p_list,
								int cycle_to_die);
int						scheduler_step(t_vm *vm);

int						read_arg_number(int argc, char **argv, int *i,
								t_vm *vm);
t_arrlst				*build_champions(int argc, char **argv, int *i);
t_visualizer			*create_visualizer(int argc, char **argv, int *i);

void					visualizer_text_init(void *data, int argc, char **argv);
void					visualizer_text_instruction_read(void *data,
															t_mem *address);
void					visualizer_text_instruction_fired(void *data,
															t_mem *address);
int						visualizer_text_program_active(void *data);
void					visualizer_text_game_over(void *vdata, t_vm *vm);
void					visualizer_text_cleanup(void *data);
t_arrlst				*visualizer_text_select_champs(void *data);
void					visualizer_text_process_lived(void *data,
							t_process *process, int champ, char *champ_name);
void					visualizer_text_memory_read(void *data, t_mem *address,
												int value, t_process *process);
void					visualizer_text_memory_written(void *data,
								t_mem *address, int value, t_process *process);
void					visualizer_text_render(void *data, t_vm *vm);
void					visualizer_text_use_champs(void *data,
															t_arrlst *champs);
void					visualizer_text_sleep(void *data);

t_visualizer			*visualizer_text_new(void);

t_visualizer			*visualizer_sdl_new(void);

#endif
