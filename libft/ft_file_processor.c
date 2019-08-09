/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:07:25 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/02 21:34:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file_processor.h"

t_file_processor	*ft_fp_init(t_lh *handlers, void *data, t_freer free_data)
{
	t_file_processor *fp;

	fp = (t_file_processor *)malloc(sizeof(t_file_processor));
	if (!fp)
		return (NULL);
	fp->line = NULL;
	fp->data = data;
	fp->free_data = free_data;
	fp->handlers = handlers;
	fp->current_handler = 0;
	return (fp);
}

static int			on_error(t_file_processor *fp, int errno)
{
	if (fp->data && fp->free_data)
		(*(fp->free_data))(fp->data);
	return (errno);
}

int					process_line(t_file_processor *fp, char *line)
{
	t_lh	handler;
	int		status;

	while (1)
	{
		handler = fp->handlers[fp->current_handler];
		if (!handler)
			return (on_error(fp, FPERR_BAD_INPUT));
		status = ((*handler)(line, fp->data));
		if (status != -1)
			return (0);
		fp->current_handler += 1;
	}
}

int					ft_fp_process_fd(t_file_processor *fp, int fd)
{
	char	*line;
	int		status;

	if (!fp)
		return (FPERR_NO_FP);
	if (fd < 0)
		return (FPERR_BAD_FD);
	while (1)
	{
		status = get_next_line(fd, &line);
		if (status == 0)
			return (0);
		else if (status == 1)
		{
			if ((status = process_line(fp, line)) != 0)
			{
				free(line);
				return (status);
			}
		}
		else if (status == -1)
			return (on_error(fp, FPERR_GNL_FAIL));
		free(line);
	}
}

int					ft_fp_process_file(t_file_processor *fp, char *filename)
{
	int fd;
	int result;

	if (!fp)
		return (FPERR_NO_FP);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FPERR_OPEN_FAIL);
	result = ft_fp_process_fd(fp, fd);
	close(fd);
	return (result);
}
