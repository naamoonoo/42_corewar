/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_indirect_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:25:05 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 17:28:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		search_forward(t_tree *tree, char *label)
{
	int		ret;
	char	*new_label;

	ret = 0;
	if (!tree)
		return (0);
	new_label = ft_strjoin(label, ":");
	if (ft_strnequ(tree->content, new_label, ft_strlen(new_label)))
	{
		free(new_label);
		return (ret);
	}
	ret = search_forward(tree->left, label);
	free(new_label);
	return (ret + tree->block_size);
}

int		search_backward(t_tree *tree, char *label)
{
	int		ret;
	char	*new_label;

	if (!tree->content)
		return (0);
	new_label = ft_strjoin(label, ":");
	if (ft_strnequ(tree->content, new_label, ft_strlen(new_label)))
	{
		free(new_label);
		return (tree->block_size);
	}
	ret = search_backward(tree->parent, label);
	free(new_label);
	return (ret + tree->block_size);
}

int		get_indirect_value(t_tree *tree, char *label)
{
	char *new_label;

	new_label = ft_strjoin(label, ":");
	if (ft_strnequ(tree->content, new_label, ft_strlen(new_label)))
	{
		free(new_label);
		return (tree->block_size * -1);
	}
	if (found_backwards(tree, label))
	{
		free(new_label);
		return (search_backward(tree, label) * -1);
	}
	else if (found_forwards(tree, label))
	{
		free(new_label);
		return (search_forward(tree, label));
	}
	else
	{
		free(new_label);
		ft_exit("Could not find label\n", NULL, 0);
	}
	return (42);
}

int		adjusted_label_value(t_tree *tree, t_tree *instruction, int value)
{
	int block_size;

	block_size = 0;
	if (value <= 0)
	{
		while (instruction)
		{
			block_size += instruction->block_size;
			instruction = instruction->right;
		}
	}
	else
	{
		while (instruction && instruction->parent != tree)
		{
			instruction = instruction->parent;
			block_size -= instruction->block_size;
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
	if (ft_strchr(nav->content, LABEL_CHAR))
		nav->value += adjusted_label_value(tree, instruction, nav->value);
}
