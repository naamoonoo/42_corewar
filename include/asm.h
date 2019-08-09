#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "op.h"

# define INPUT fd[0]
# define OUTPUT fd[1]

void    		parse_registry(int *fd);
void    		parse_indirect(int *fd);
void    		parse_direct(int *fd, t_op op_tab);
void			decode(int *fd, t_op op_tab);
void			no_decode(int *fd, t_op op_tab);
char    		*read_dir_ind(int *fd);
char    		*read_dir(int *fd);
int				dasm(char *input_file, char *output_name, int *fd);
int				extension_check(const char *file, char *extension);

#endif
