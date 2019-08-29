/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_indirect_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:22:11 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:04:58 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	search_instruction_list(t_tree *tree, t_tree *instruction)
{
	int	i;

	i = 0;
	while (i < instruction->operation->param_num)
	{
		if (instruction->arg_type[i] == DIR_CODE)
			edit_indirect_value(tree, instruction, i);
		i++;
	}
	if (instruction->right)
		search_instruction_list(tree, instruction->right);
}

void	parse_indirect_values(t_tree *tree)
{
	t_tree *nav;

	nav = tree;
	if (tree->content)
		if (tree->right)
			search_instruction_list(tree, tree->right);
	if (tree->left)
		parse_indirect_values(tree->left);
}
