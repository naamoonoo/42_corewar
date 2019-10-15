/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 11:00:52 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 16:33:01 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <libft.h>
# include <op.h>

# define WHITE_SPACE " \f\v\t\r\n\""
# define COMMENT_DELIMS " \f\v\t\r\n\""
# define INPUT fd[0]
# define OUTPUT fd[1]
# define NULL_FUNCTION 0
# define NAME_COMMENT_FUNCTION 1
# define LABEL_FUNCTION 2
# define ERROR_FUNCTION 3
# define INSTRUCTION_FUNCTION 4
# define _REG_SIZE 1
# define _DIR_SIZE 4
# define _IND_SIZE 2

typedef struct		s_tree
{
	char			*content;
	int				block_size;
	int				line_num;
	int				instruction;
	int				value;
	t_op			*operation;
	t_arg_type		arg_type[3];
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*name_comment;
	struct s_tree	*parent;
}					t_tree;

extern t_op			g_op_tab[17];
extern void			(*g_parse_function[])(t_tree **t, char **s, int l, int *f);

void				parse_label(t_tree **t, char **s, int line_num, int *fd);
void				parse_name_comment(t_tree **t, char **s, int l, int *fd);
void				parse_error(t_tree **tree, char **split, int l, int *fd);
void				parse_instruction(t_tree **t, char **s, int l, int *fd);

int					ft_error(char *str, int i);
void				parse_registry(int *fd);
void				parse_indirect(int *fd);
void				parse_direct(int *fd, t_op op_tab);
void				decode(int *fd, t_op op_tab);
void				no_decode(int *fd, t_op op_tab);
char				*read_dir_ind(int *fd);
char				*read_dir(int *fd);
int					dasm(char *input_file, char *output_name, int *fd);
int					extension_check(const char *file, char *extension);
int					search_forward(t_tree *tree, char *label);
int					search_backward(t_tree *tree, char *label);
int					get_indirect_value(t_tree *tree, char *label);
int					adjusted_label_value(t_tree *t, t_tree *instruct, int v);
void				edit_indirect_value(t_tree *tree, t_tree *instruct, int a);
void				search_instruction_list(t_tree *tree, t_tree *instruction);
void				parse_indirect_values(t_tree *tree);
void				ft_exit(char *reason, char **split, int line_num);
int					outout_name_check(char *input_file, char *output_name);
int					disassemble(int *fd, char c);
int					comment_name_get(int *fd);
int					found_backwards(t_tree *tree, char *label);
int					found_forwards(t_tree *tree, char *label);

void				get_header_comment(t_header *header, t_tree *tree);
void				get_header_name(t_header *header, t_tree *tree);
void				write_comment_to_file(t_tree *tree, int *fd);

void				write_int(int value, int *fd);
void				write_short(short value, int *fd);

void				tree_parse_error(char *reason, t_tree *tree);

int					parse_direct_type(char *arg, t_tree *tree, t_tree *i);
int					parse_indirect_type(char *arg, t_tree *tree, t_tree *i);
int					parse_reg_type(char *arg, t_tree *tree, t_tree *i);
int					get_block_size(t_tree *tree);
void				parse_tree(t_tree *tree);

int					ide_mixed_type(t_tree *t, char *a, t_arg_type y, t_tree *i);
int					ide_arg_type(t_tree *t, char *a, t_arg_type y, t_tree *in);

int					ft_error(char *str, int i);
void				ft_exit(char *reason, char **split, int line_num);
void				parse_error(t_tree **tree, char **split, int num, int *fd);
void				tree_parse_error(char *reason, t_tree *tree);

int					get_name(char *file);
char				*remove_front_spaces(char *str);
void				ft_free_split_string(char **split);
void				init_tree(t_tree **tree, char *str, int line_num);
t_tree				*create_branch(t_tree *parent, char *str, int line_num);

void				store_name_comment(t_tree **tree, char *str, int line_num);
void				fill_comment_data(t_tree **t, char **split, int line_num);
void				parse_name_comment(t_tree **t, char **s, int l, int *fd);

int					identify_line(char *line);
void				parser(int *fd, t_tree **tree, int line_num);

void				store_instruction_arg(t_tree **t, char *s, int l, int y);
int					identify_instruction(char *str);
void				fill_instruction_data(t_tree **t, char **s, int line_num);
void				parse_instruction(t_tree **tree, char **s, int l, int *fd);

void				parse_label(t_tree **tree, char **s, int line_num, int *fd);

void				write_to_file(t_tree *tree, int *fd);
void				wirte_arg_block(t_tree *tree, t_tree *parent, int *fd);
char				get_encoding_byte(t_arg_type arg_type[3], int param_num);

int					assemble(char *file);

void				parse_registry(int *fd);
void				parse_indirect(int *fd);
void				parse_direct(int *fd, t_op op_tab);
char				*read_dir_ind(int *fd);
char				*read_dir(int *fd);

#endif
