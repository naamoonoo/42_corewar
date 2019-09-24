/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:28:23 by aderby            #+#    #+#             */
/*   Updated: 2019/08/24 21:25:59 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		get_name(char *file)
{
	char	*name;
	char	*ptr;
	int		fd;

	ptr = ft_strchr(file, '.');
	ptr = ft_strsub(file, 0, ptr - file);
	name = ft_strjoin(ptr, ".cor");
	ft_printf("%s", "writing output to file ");
	ft_printf("%s\n", name);
	free(ptr);
	fd = open(name, O_CREAT | O_RDWR, 0644);
	free(name);
	if (!fd)
		return (ft_error("The output file could not be created.\n", 0));
	return (fd);
}

char	*remove_front_spaces(char *str)
{
	char	*clean_str;

	clean_str = str;
	while ((
				*clean_str == ' ' ||
				*clean_str == '\t' ||
				*clean_str == '\v' ||
				*clean_str == '\n') && *clean_str)
		clean_str++;
	return (clean_str);
}

void	init_tree(t_tree **tree, char *str, int line_num)
{
	*tree = (t_tree*)malloc(sizeof(t_tree));
	(*tree)->content = (str == NULL) ? NULL : ft_strdup(str);
	(*tree)->block_size = 0;
	(*tree)->line_num = line_num;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	(*tree)->name_comment = NULL;
	(*tree)->parent = NULL;
	(*tree)->operation = NULL;
	(*tree)->arg_type[0] = 0;
	(*tree)->arg_type[1] = 0;
	(*tree)->arg_type[2] = 0;
}

t_tree	*create_branch(t_tree *parent, char *str, int line_num)
{
	t_tree *new;

	new = (t_tree*)malloc(sizeof(t_tree));
	new->content = (str == NULL) ? NULL : ft_strdup(str);
	new->block_size = 0;
	new->instruction = 0;
	new->arg_type[0] = 0;
	new->arg_type[1] = 0;
	new->arg_type[2] = 0;
	new->value = 0;
	new->line_num = line_num;
	new->left = NULL;
	new->right = NULL;
	new->name_comment = NULL;
	new->parent = parent;
	new->operation = NULL;
	return (new);
}

void	ft_free_split_string(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_bzero(split[i], ft_strlen(split[i]));
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}
