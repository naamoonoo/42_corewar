/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:46:55 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 17:29:51 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	free_tree(t_tree *tree)
{
	if (tree)
	{
		if (tree->right)
			free_tree(tree->right);
		if (tree->left)
			free_tree(tree->left);
		if (tree->name_comment)
			free_tree(tree->name_comment);
		if (tree->content)
		{
			free(tree->content);
			tree->content = NULL;
		}
		free(tree);
		tree = NULL;
	}
}

int		assemble(char *file)
{
	int		fd[2];
	t_tree	*tree;

	tree = NULL;
	if (!extension_check(file, ".s"))
		return (ft_error("The file must have the .s extension\n", 0));
	INPUT = open(file, O_RDONLY);
	if (INPUT <= 0)
		return (ft_error("Unable to open <file>.s\n", 0));
	parser(fd, &tree, 0);
	parse_tree(tree);
	parse_indirect_values(tree);
	if (!(OUTPUT = get_name(file)))
		return (ft_error("Unable to create the output file.\n", 0));
	write_comment_to_file(tree, fd);
	write_to_file(tree, fd);
	free_tree(tree);
	return (1);
}
