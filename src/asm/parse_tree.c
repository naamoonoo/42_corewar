/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:57:28 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 17:08:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		parse_direct_type(char *arg, t_tree *tree, t_tree *instruction)
{
	int i;

	i = 0;
	if (arg[0] != DIRECT_CHAR || arg[0] == LABEL_CHAR)
		tree_parse_error("Incorrect argument type\n", tree);
	tree->value = ft_atoi(arg + 1);
	while (i < 3 && instruction->arg_type[i])
		i++;
	if (i < 3)
		instruction->arg_type[i] = DIR_CODE;
	return ((instruction->operation->dir_ind) ? _IND_SIZE : _DIR_SIZE);
}

int		parse_indirect_type(char *arg, t_tree *tree, t_tree *instruction)
{
	int i;

	i = 0;
	if (ft_strchr(arg, DIRECT_CHAR) || ft_strchr(arg, LABEL_CHAR))
		tree_parse_error("Incorrect argument type\n", tree);
	tree->value = ft_atoi(arg);
	while (i < 3 && instruction->arg_type[i])
		i++;
	if (i < 3)
		instruction->arg_type[i] = IND_CODE;
	return (_IND_SIZE);
}

int		parse_reg_type(char *arg, t_tree *tree, t_tree *instruction)
{
	int	i;

	i = 0;
	if (arg[0] != 'r')
		tree_parse_error("Incorrect argument type\n", tree);
	tree->value = ft_atoi(arg + 1);
	if (ft_strlen(arg) > 3 || tree->value < 0)
		tree_parse_error("Register value must be positive between 0 and 99\n"
				, tree);
	if (tree->value < 0 || tree->value > REG_NUMBER)
		tree_parse_error("Incorrect Registry number\n", tree);
	while (i < 3 && instruction->arg_type[i])
		i++;
	if (i < 3)
		instruction->arg_type[i] = REG_CODE;
	return (_REG_SIZE);
}

int		get_block_size(t_tree *tree)
{
	int		i;
	int		size;
	t_tree	*nav;

	i = 0;
	size = 1;
	if (tree->operation->encode)
		size++;
	nav = tree;
	while (i < tree->operation->param_num)
	{
		if (!nav->left)
			tree_parse_error("Incorrect number of arguments\n", tree);
		nav = nav->left;
		size += ide_arg_type(nav, nav->content,
				tree->operation->arg_type[i], tree);
		i++;
	}
	tree->block_size = size;
	return ((tree->right) ? (get_block_size(tree->right) + size) : size);
}

void	parse_tree(t_tree *tree)
{
	if (!tree)
		ft_exit("Nothing to assemble.\n", NULL, 0);
	if (tree->content)
	{
		if (tree->right)
			tree->block_size = get_block_size(tree->right);
		if (tree->left)
			parse_tree(tree->left);
	}
	else
	{
		if (tree->right)
			get_block_size(tree->right);
		if (tree->left)
			parse_tree(tree->left);
	}
}
