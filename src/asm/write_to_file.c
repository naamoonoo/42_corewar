/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:44:12 by aderby            #+#    #+#             */
/*   Updated: 2019/08/20 11:05:36 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

char	get_encoding_byte(t_arg_type arg_type[3], int param_num)
{
	int				i;
	unsigned char	encoding_byte;

	i = 0;
	encoding_byte = 0;
	while (i < param_num)
	{
		encoding_byte = encoding_byte ^ (arg_type[i] << (6 - (2 * i)));
		i++;
	}
	return (encoding_byte);
}

void	write_arg(t_tree *tree, t_tree *nav, t_arg_type arg_t, int *fd)
{
	if (arg_t == DIR_CODE)
	{
		if (tree->operation->dir_ind)
		{
			if (ft_strchr(nav->content, DIRECT_CHAR))
			{
				if (ft_strchr(nav->content, LABEL_CHAR))
					write_short(nav->value, fd);
				else
					write_short(ft_atoi(nav->content + 1), fd);
			}
			else
				write_short(ft_atoi(nav->content), fd);
		}
		else
			write_int(ft_atoi(nav->content + 1), fd);
	}
	else if (arg_t == IND_CODE)
		write_short(nav->value, fd);
	else
		write(OUTPUT, (char[1]){nav->value}, 1);
}

void	write_arg_block(t_tree *tree, t_tree *parent, int *fd)
{
	t_tree		*nav;
	int			i;
	t_arg_type	*arg_type;
	char		enc;

	nav = tree;
	arg_type = tree->arg_type;
	i = 0;
	write(OUTPUT, (char[1]){nav->operation->op_num}, 1);
	if (nav->operation->encode)
	{
		enc = get_encoding_byte(nav->arg_type, nav->operation->param_num);
		write(OUTPUT, &enc, 1);
	}
	while (nav->left)
	{
		nav = nav->left;
		write_arg(tree, nav, arg_type[i], fd);
		i++;
	}
	if (tree->right)
		write_arg_block(tree->right, parent, fd);
}

void	write_to_file(t_tree *tree, int *fd)
{
	t_tree *nav;

	nav = tree;
	if (nav->right)
		write_arg_block(nav->right, tree, fd);
	if (nav->left)
		write_to_file(nav->left, fd);
}
