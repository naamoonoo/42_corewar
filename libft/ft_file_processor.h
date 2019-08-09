/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_processor.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:07:25 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 15:28:41 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_PROCESSOR_H
# define FT_FILE_PROCESSOR_H

# include <fcntl.h>
# include "libft.h"

typedef int			(*t_lh)(const char *line, void *data);
typedef void		(*t_freer)(void *data);

typedef struct		s_file_processor
{
	char			*line;
	void			*data;
	void			(*free_data)(void *);
	t_lh			*handlers;
	int				current_handler;
}					t_file_processor;

# define FPERR_NO_FP 1
# define FPERR_OPEN_FAIL 2
# define FPERR_BAD_FD 3
# define FPERR_GNL_FAIL 4
# define FPERR_BAD_INPUT 5

t_file_processor	*ft_fp_init(t_lh *handlers, void *data, t_freer free_data);
int					ft_fp_process_fd(t_file_processor *fp, int fd);
int					ft_fp_process_file(t_file_processor *fp, char *filename);

#endif
