/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:42:30 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:05:15 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	parse_label(t_tree **tree, char **split, int line_num, int *fd)
{
	t_tree	*nav;

	if (!*tree)
		init_tree(tree, split[0], line_num);
	else
	{
		nav = *tree;
		while (nav->left)
			nav = nav->left;
		nav->left = create_branch(nav, split[0], line_num);
	}
	if (split[1])
		parse_instruction(tree, split + 1, line_num, fd);
}
