/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 19:47:48 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 17:06:49 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		ft_error(char *str, int i)
{
	ft_fdprintf(2, "%s", str);
	return (i);
}

void	ft_exit(char *reason, char **split, int line_num)
{
	int i;

	i = -1;
	ft_error("Parse Error on line ", 0);
	ft_fdprintf(2, "%d\n", line_num);
	if (split)
	{
		while (split[++i])
		{
			ft_error(split[i], 0);
			ft_error(" ", 0);
		}
		ft_error("\n", 0);
	}
	ft_error(reason, 0);
	exit(0);
}

void	parse_error(t_tree **tree, char **split, int line_num, int *fd)
{
	(void)fd;
	(void)tree;
	(void)split;
	(void)line_num;
	ft_error("This is an error in parse error\n", 0);
	ft_printf("%d\n", line_num);
}

void	tree_parse_error(char *reason, t_tree *tree)
{
	ft_error("Parse error on line ", 0);
	ft_fdprintf(2, "%d\n", tree->line_num);
	ft_error("\n", 0);
	ft_error(reason, 0);
	ft_error("\n", 0);
	while (tree)
	{
		ft_error(tree->content, 0);
		tree = tree->left;
	}
	exit(0);
}
