/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_name_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:51:12 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 13:10:25 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void			get_header_comment(t_header *header, t_tree *tree)
{
	t_tree *nav;

	nav = tree;
	while (nav->name_comment)
	{
		nav = nav->name_comment;
		if (ft_strequ(nav->content, COMMENT_CMD_STRING))
		{
			while (nav->left)
			{
				nav = nav->left;
				ft_strcat(header->comment, nav->content);
				if (nav->left)
					ft_strcat(header->comment, " ");
			}
		}
	}
}

void			get_header_name(t_header *header, t_tree *tree)
{
	t_tree *nav;

	nav = tree;
	while (nav->name_comment)
	{
		nav = nav->name_comment;
		if (ft_strequ(nav->content, NAME_CMD_STRING))
		{
			while (nav->left)
			{
				nav = nav->left;
				ft_strcat(header->prog_name, nav->content);
				if (nav->left)
					ft_strcat(header->prog_name, " ");
			}
		}
	}
}

unsigned int	get_prog_size(t_tree *tree)
{
	t_tree	*nav;
	int		prog_size;

	nav = tree;
	prog_size = 0;
	while (nav)
	{
		prog_size += nav->block_size;
		nav = nav->left;
	}
	return (prog_size);
}

void			write_comment_to_file(t_tree *tree, int *fd)
{
	t_header	header;
	t_tree		*nav;

	nav = tree;
	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header.comment, COMMENT_LENGTH + 1);
	write_int(COREWAR_EXEC_MAGIC, fd);
	header.prog_size = get_prog_size(tree);
	get_header_name(&header, tree);
	get_header_comment(&header, tree);
	write(OUTPUT, header.prog_name, PROG_NAME_LENGTH);
	write(OUTPUT, (char[4]){0}, 4);
	write_int(get_prog_size(tree), fd);
	write(OUTPUT, header.comment, COMMENT_LENGTH);
	write(OUTPUT, (char[4]){0}, 4);
}
