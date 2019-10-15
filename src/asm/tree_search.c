/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:25:05 by aderby            #+#    #+#             */
/*   Updated: 2019/09/27 17:25:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		found_backwards(t_tree *tree, char *label)
{
	t_tree	*nav;
	char	*new_label;

	nav = tree;
	if (!tree)
		return (0);
	new_label = ft_strjoin(label, ":");
	while (nav && nav->content)
	{
		if (ft_strnequ(nav->content, new_label, ft_strlen(new_label)))
		{
			free(new_label);
			return (1);
		}
		nav = nav->parent;
	}
	free(new_label);
	return (0);
}

int		found_forwards(t_tree *tree, char *label)
{
	t_tree	*nav;
	char	*new_label;

	nav = tree;
	if (!tree)
		return (0);
	new_label = ft_strjoin(label, ":");
	while (nav && nav->content)
	{
		if (ft_strnequ(nav->content, new_label, ft_strlen(new_label)))
		{
			free(new_label);
			return (1);
		}
		nav = nav->left;
	}
	free(new_label);
	return (0);
}
