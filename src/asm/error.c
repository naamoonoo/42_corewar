/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 19:47:48 by aderby            #+#    #+#             */
/*   Updated: 2019/08/22 15:18:09 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		ft_error(char *str, int i)
{
	ft_putstr(str);
	return (i);
}

void	ft_exit(char *reason, char **split, int line_num)
{
	int i;

	i = -1;
	ft_putstr("Parse Error on line ");
	ft_putnbr(line_num);
	ft_putstr("\n");
	if (split)
	{
		while (split[++i])
		{
			ft_putstr(split[i]);
			ft_putstr(" ");
		}
		ft_putstr("\n");
	}
	ft_putstr(reason);
	exit(0);
}

void	parse_error(t_tree **tree, char **split, int line_num, int *fd)
{
	(void)fd;
	(void)tree;
	(void)split;
	(void)line_num;
	ft_putstr("This is an error in parse error\n");
	printf("%d\n", line_num);
}

void	tree_parse_error(char *reason, t_tree *tree)
{
	ft_putstr("Parse error on line ");
	ft_putnbr(tree->line_num);
	ft_putstr("\n");
	ft_putstr(reason);
	ft_putstr("\n");
	while (tree)
	{
		ft_putstr(tree->content);
		tree = tree->left;
	}
	exit(0);
}
