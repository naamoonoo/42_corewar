/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:30:42 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 13:08:39 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	store_name_comment(t_tree **tree, char *str, int line_num)
{
	t_tree *nav;

	nav = *tree;
	while (nav->left)
		nav = nav->left;
	nav->left = create_branch(*tree, str, line_num);
}

void	fill_comment_data(t_tree **tree, char **split, int line_num)
{
	int	i;

	i = 0;
	while (split[++i])
		store_name_comment(tree, split[i], line_num);
}

void	parse_name_comment(t_tree **tree, char **split, int line_num, int *fd)
{
	t_tree	*nav;
	int		i;

	(void)fd;
	i = 0;
	if (!*tree)
		init_tree(tree, "NULL", line_num);
	nav = *tree;
	while (nav->name_comment)
	{
		nav = nav->name_comment;
		i++;
	}
	if (i > 1)
		ft_exit("There should only be one name and comment\n",
				split, line_num);
	nav->name_comment = create_branch(nav, split[0], line_num);
	fill_comment_data(&nav->name_comment, split, line_num);
}
