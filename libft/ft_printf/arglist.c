/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:56:44 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 13:52:10 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_arglist	*new_arglist(void)
{
	t_arglist *arglist;

	arglist = (t_arglist *)malloc(sizeof(t_arglist));
	if (arglist == NULL)
		return (NULL);
	arglist->args = 0;
	arglist->size = 0;
	return (arglist);
}

static int	expand_arglist(t_arglist *arglist, int new_size)
{
	t_argument **tmp;

	if (new_size <= arglist->size)
		return (1);
	tmp = arglist->args;
	arglist->args = (t_argument **)malloc(new_size * sizeof(t_argument *));
	if (arglist->args == NULL)
		return (0);
	ft_bzero(arglist->args, new_size * sizeof(t_argument *));
	ft_memcpy(arglist->args, tmp, arglist->size * sizeof(t_argument *));
	if (tmp)
		free(tmp);
	arglist->size = new_size;
	return (1);
}

/*
** Potential memory leak on 0 return if arglist is not freed
*/

int			set_arg_type(t_arglist *arglist, int index, ARGSIZE type)
{
	t_argument *arg;

	if (arglist == NULL || index < 1)
		return (0);
	if (index > arglist->size)
		if (!expand_arglist(arglist, index))
			return (0);
	if (arglist->args[index - 1] == NULL)
	{
		arglist->args[index - 1] = (t_argument *)malloc(sizeof(t_argument));
		if (arglist->args[index - 1] == NULL)
			return (0);
	}
	arg = arglist->args[index - 1];
	arg->type = type;
	arg->data = NULL;
	return (1);
}

void		free_arglist(t_arglist **arglist)
{
	int			i;
	t_argument	**args;

	i = 0;
	if ((arglist == NULL) || (*arglist == NULL))
		return ;
	args = (*arglist)->args;
	while (i < (*arglist)->size)
	{
		if (args[i])
		{
			if (args[i]->data)
				free(args[i]->data);
			free(args[i]);
		}
		i++;
	}
	free(args);
	free(*arglist);
	*arglist = NULL;
}
