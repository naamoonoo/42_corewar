/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_indirect_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:25:05 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:03:50 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		search_forward(t_tree *tree, char *label)
{
	int		ret;

	if (!tree)
		return (0);
	if (ft_strnequ(tree->content, label, ft_strlen(label)))
		return (tree->block_size);
	ret = search_forward(tree->left, label);
	return ((ret) ? ret + tree->block_size : ret);
}

int		search_backward(t_tree *tree, char *label)
{
	int ret;

	if (!tree)
		return (0);
	if (ft_strnequ(tree->content, label, ft_strlen(label)))
		return (tree->block_size);
	ret = search_backward(tree->parent, label);
	return ((ret) ? ret + tree->block_size : ret);
}

int		get_indirect_value(t_tree *tree, char *label)
{
	int ret;

	ret = search_backward(tree->parent, label);
	return ((ret) ? ret * -1 : search_forward(tree->left, label));
}

int		adjusted_label_value(t_tree *tree, t_tree *instruction, int value)
{
	int block_size;

	block_size = 0;
	if (value <= 0)
	{
		while (instruction && instruction != tree)
		{
			block_size -= instruction->block_size;
			instruction = instruction->parent;
		}
	}
	else
	{
		while (instruction)
		{
			block_size += instruction->block_size;
			instruction = instruction->right;
		}
	}
	return (block_size);
}

void	edit_indirect_value(t_tree *tree, t_tree *instruction, int arg_num)
{
	t_tree *nav;

	nav = instruction;
	while (arg_num >= 0)
	{
		if (!nav->left)
			ft_exit("Unknown Parse Error\n", NULL, instruction->line_num);
		nav = nav->left;
		arg_num--;
	}
	nav->value = (ft_strchr(nav->content, LABEL_CHAR))
		? get_indirect_value(tree, nav->content + 2)
		: ft_atoi(nav->content);
	nav->value += adjusted_label_value(tree, instruction, nav->value);
}
