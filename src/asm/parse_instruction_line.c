/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:38:01 by aderby            #+#    #+#             */
/*   Updated: 2019/08/30 21:19:38 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	store_instruction_arg(t_tree **tree, char *str, int line_num, int type)
{
	t_tree	*nav;

	nav = *tree;
	while (nav->left)
		nav = nav->left;
	nav->left = create_branch(nav, str, line_num);
	nav->left->operation = &g_op_tab[type];
}

int		identify_instruction(char *str)
{
	int	i;

	i = 0;
	while (g_op_tab[i].name != 0)
	{
		if (ft_strequ(str, g_op_tab[i].name))
			return (i);
		i++;
	}
	return (i);
}

void	fill_instruction_data(t_tree **tree, char **split, int line_num)
{
	int i;
	int	type;

	i = 0;
	type = identify_instruction(split[0]);
	if (type > 15)
		ft_exit("Invalid instruction\n", split, line_num);
	(*tree)->operation = &g_op_tab[type];
	(*tree)->instruction = type;
	while (split[++i])
		store_instruction_arg(tree, split[i], line_num, type);
}

void	parse_instruction(t_tree **tree, char **split, int line_num, int *fd)
{
	(void) fd; // TODO 
	t_tree *nav;

	if (!*tree)
		init_tree(tree, NULL, line_num);
	nav = *tree;
	while (nav->left)
		nav = nav->left;
	while (nav->right)
		nav = nav->right;
	nav->right = create_branch(nav, split[0], line_num);
	fill_instruction_data(&nav->right, split, line_num);
}
