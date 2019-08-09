/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:47:09 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/09 17:59:56 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Creates a new t_fragment, initializing the size to 0 and the data to NULL.
*/

t_fragment	*new_fragment(void)
{
	t_fragment	*frag;

	frag = (t_fragment *)malloc(sizeof(t_fragment));
	if (frag == 0)
		return (0);
	frag->size = 0;
	frag->data = 0;
	return (frag);
}

/*
** Removes everything up to the first newline character in frag->data, placing
** the removed characters into a new string *line. Returns 1 if successful, 0 if
** no newline character could be found, and -1 on malloc error.
*/

int			pop_line(t_fragment *frag, char **line)
{
	int		i;

	i = 0;
	while (i < frag->size)
	{
		if (frag->data[i] == '\n')
		{
			*line = (char *)malloc((i + 1) * sizeof(char));
			if (*line == 0)
				return (-1);
			ft_memcpy(*line, frag->data, i);
			(*line)[i] = 0;
			ft_memmove(frag->data, frag->data + i + 1, frag->size - i - 1);
			frag->size = frag->size - i - 1;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Reads up to BUFF_SIZE bytes from the file descriptor fd and appends the data
** to frag->data. Returns 1 if successful, 0 on end of file, and -1 on malloc
** error.
*/

int			add_next_buff(t_fragment *frag, const int fd)
{
	unsigned long	bytes_read;
	char			buffer[BUFF_SIZE];
	char			*prev_data;

	bytes_read = read(fd, buffer, BUFF_SIZE);
	if (bytes_read < 1)
		return (bytes_read);
	if (frag->data == 0)
	{
		frag->data = (char *)malloc(bytes_read * sizeof(char));
		if (frag->data == 0)
			return (-1);
		ft_memcpy(frag->data, buffer, bytes_read);
		frag->size = bytes_read;
	}
	else
	{
		prev_data = frag->data;
		frag->data = (char *)malloc((frag->size + bytes_read) * sizeof(char));
		ft_memcpy(frag->data, prev_data, frag->size);
		free(prev_data);
		ft_memcpy(frag->data + frag->size, buffer, bytes_read);
		frag->size = frag->size + bytes_read;
	}
	return (1);
}

/*
** This function is just to handle if the last part of a file is not terminated
** by a newline. If so, it will push the remaining characters into line and
** return 1 (or -1 on malloc error). If there is nothing left in the fragment
** it will return 0.
*/

int			finalize(t_fragment *frag, char **line)
{
	if (frag->size != 0)
	{
		*line = (char *)malloc((frag->size + 1) * sizeof(char));
		if (line == 0)
			return (-1);
		ft_memcpy(*line, frag->data, frag->size);
		(*line)[frag->size] = 0;
		frag->size = 0;
		return (1);
	}
	return (0);
}

/*
** get_next_line
*/

int			get_next_line(const int fd, char **line)
{
	static t_fragment	*frags[65536];
	int					status;

	if (fd < 0 || fd > 65535)
		return (-1);
	if (line == 0)
		return (-1);
	if (BUFF_SIZE <= 0 || BUFF_SIZE > 0xffffffffffffffff)
		return (-1);
	if (frags[fd] == 0)
		frags[fd] = new_fragment();
	if (frags[fd] == 0)
		return (-1);
	while (1)
	{
		status = pop_line(frags[fd], line);
		if (status != 0)
			return (status);
		status = add_next_buff(frags[fd], fd);
		if (status == -1)
			return (-1);
		else if (status == 0)
			return (finalize(frags[fd], line));
	}
}
